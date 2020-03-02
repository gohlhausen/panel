// S16_LE is short datatype
/// 3.011292346 hZ per bin (bin spacing)

#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"
#include "pixel-mapper.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <string.h>

#include <algorithm>
#include <alsa/asoundlib.h>
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using std::min;
using std::max;
using namespace rgb_matrix;
	      
// macros for the real and imaginary parts
#define REAL 0
#define IMAG 1
#define N 16384
#define maxbins 256
#define buffers 16
#define buffer_frames 2048
//1024


double window[N];
fftw_complex xL[N];
fftw_complex xR[N];
fftw_complex yL[N];
fftw_complex yR[N];
double mL[N/2];
double mR[N/2];
double PanelBinsL[64][maxbins+3];
double PanelBinsR[64][maxbins+3];
int CurrentPanelBin;
fftw_plan Lplan = fftw_plan_dft_1d(N, xL, yL, FFTW_FORWARD, FFTW_ESTIMATE);
fftw_plan Rplan = fftw_plan_dft_1d(N, xR, yR, FFTW_FORWARD, FFTW_ESTIMATE);
ThreadedCanvasManipulator *image_gen = NULL;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}
void setupPanelBins(){
int bin,i;
	CurrentPanelBin=0;
	for(i=0;i<64;i++){
	   for(bin=0;bin<maxbins;bin++){
		PanelBinsL[i][bin]=(double)bin/(double)maxbins;
		PanelBinsR[i][bin]=1.0-((double)bin/(double)maxbins);
		}
       	    PanelBinsL[i][maxbins+2]=1.0;
	    PanelBinsR[i][maxbins+2]=1.0;
	}
}
void makeWindow(){
	for(int i=0;i<N;i++){
	window[i]=0.5-0.5*cos((2.0*M_PI*i)/(N-i));
	}
}
class updatePanel : public ThreadedCanvasManipulator {
public:
  updatePanel(Canvas *m) : ThreadedCanvasManipulator(m) {}
  void Run() {
	int currow;
    int starty=16;
    int x,y;
    const int width = canvas()->width();
    const int height = canvas()->height();
    while (running() && !interrupt_received) {
      for (y = 0; y < height-starty; ++y) {
	currow=(64+(CurrentPanelBin-y))%64;
        for (x = 0; x < width; ++x) {
          canvas()->SetPixel(x, y+starty, (uint8_t)((PanelBinsL[currow][x+1]/PanelBinsL[currow][maxbins+2])*255.0),  (uint8_t)((PanelBinsR[currow][x+1]/PanelBinsR[currow][maxbins+2])*255.0),(((x+1+7)%25)==0)?(128):(0)); 
        }
      }
      for (x = 0; x < width; ++x) {
          canvas()->SetPixel(x, 0, (uint8_t)((PanelBinsL[CurrentPanelBin][x+1]/PanelBinsL[CurrentPanelBin][maxbins+2])*255.0),  (uint8_t)((PanelBinsR[CurrentPanelBin][x+1]/PanelBinsR[CurrentPanelBin][maxbins+2])*255.0),0); 
      }
    }
  }
};


struct Color HSVtoColor(double H, double S, double V) {
	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;
	struct Color retcolor;

	if(H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	else if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	else if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	else if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	else if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;	
	}
	
	retcolor.r = (uint8_t)((Rs + m) * 255);
	retcolor.g = (uint8_t)((Gs + m) * 255);
	retcolor.b = (uint8_t)((Bs + m) * 255);
	return(retcolor);
}



struct Color PixelColor(double volL, double volR){
/*
Right=240 hue
Left=0 Hue
Sat=100 always
Lum=0 to 50 or 0 to 75
m1,m2 should be volume related
  x1 = Math.cos(hue1 / 180 * Math.PI) * saturation1;
  y1 = Math.sin(hue1 / 180 * Math.PI) * saturation1;
  z1 = lightness1;
  x2 = Math.cos(hue2 / 180 * Math.PI) * saturation2;
  y2 = Math.sin(hue2 / 180 * Math.PI) * saturation2;
  z2 = lightness2;
  magmax=m1+m2;
  mag1=m1/magmax;
  mag2=m2/magmax;
  x=(x1*mag1)+(x2*mag2);
  y=(y1*mag1)+(y2*mag2);
  z=(z1+z2)/2;
  h = Math.atan2(y, x) * 180 / Math.PI;
  s = Math.sqrt(x * x + y * y);
  l = z;
*/
double h=0.0;
double s=0.0;
double l=0.0;
return(HSVtoColor(h,s,l));
}

/* Computes the 1-D fast Fourier transform. */
void fft(fftw_complex *in, fftw_complex *out)
{
	// create a DFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
}


double getMagnitude(fftw_complex y)
{
		return(sqrt(y[IMAG]*y[IMAG]+y[REAL]*y[REAL]));
}
double sumbins(double sbins[],int startb, int endb)
{
double retval=0;
	for(int i=startb;i<=endb;i++){
		retval+=sbins[i];
		}

	return(retval);
}

void makebins(double bins[], double yL[]){
// bins[0]=average value
// bins[256+1]=max value across all bins(not 0)
double maxL=0;
double sumL=0;
bins[0]=sumbins(yL,0,0);
bins[1]=sumbins(yL,1,6);
bins[2]=sumbins(yL,7,7);
bins[3]=sumbins(yL,7,7);
bins[4]=sumbins(yL,7,7);
bins[5]=sumbins(yL,8,8);
bins[6]=sumbins(yL,8,8);
bins[7]=sumbins(yL,8,8);
bins[8]=sumbins(yL,8,8);
bins[9]=sumbins(yL,8,8);
bins[10]=sumbins(yL,9,9);
bins[11]=sumbins(yL,9,9);
bins[12]=sumbins(yL,9,9);
bins[13]=sumbins(yL,9,9);
bins[14]=sumbins(yL,10,10);
bins[15]=sumbins(yL,10,10);
bins[16]=sumbins(yL,10,10);
bins[17]=sumbins(yL,11,11);
bins[18]=sumbins(yL,11,11);
bins[19]=sumbins(yL,11,11);
bins[20]=sumbins(yL,11,11);
bins[21]=sumbins(yL,12,12);
bins[22]=sumbins(yL,12,12);
bins[23]=sumbins(yL,12,12);
bins[24]=sumbins(yL,13,13);
bins[25]=sumbins(yL,13,13);
bins[26]=sumbins(yL,14,14);
bins[27]=sumbins(yL,14,14);
bins[28]=sumbins(yL,14,14);
bins[29]=sumbins(yL,15,15);
bins[30]=sumbins(yL,15,15);
bins[31]=sumbins(yL,16,16);
bins[32]=sumbins(yL,16,16);
bins[33]=sumbins(yL,16,16);
bins[34]=sumbins(yL,17,17);
bins[35]=sumbins(yL,17,17);
bins[36]=sumbins(yL,18,18);
bins[37]=sumbins(yL,18,18);
bins[38]=sumbins(yL,19,19);
bins[39]=sumbins(yL,19,19);
bins[40]=sumbins(yL,20,20);
bins[41]=sumbins(yL,20,20);
bins[42]=sumbins(yL,21,21);
bins[43]=sumbins(yL,22,22);
bins[44]=sumbins(yL,22,22);
bins[45]=sumbins(yL,23,23);
bins[46]=sumbins(yL,24,24);
bins[47]=sumbins(yL,24,24);
bins[48]=sumbins(yL,25,25);
bins[49]=sumbins(yL,26,26);
bins[50]=sumbins(yL,26,26);
bins[51]=sumbins(yL,27,27);
bins[52]=sumbins(yL,28,28);
bins[53]=sumbins(yL,29,29);
bins[54]=sumbins(yL,29,29);
bins[55]=sumbins(yL,30,30);
bins[56]=sumbins(yL,31,31);
bins[57]=sumbins(yL,32,32);
bins[58]=sumbins(yL,33,33);
bins[59]=sumbins(yL,34,34);
bins[60]=sumbins(yL,35,35);
bins[61]=sumbins(yL,36,36);
bins[62]=sumbins(yL,37,37);
bins[63]=sumbins(yL,38,38);
bins[64]=sumbins(yL,39,39);
bins[65]=sumbins(yL,40,40);
bins[66]=sumbins(yL,41,41);
bins[67]=sumbins(yL,42,42);
bins[68]=sumbins(yL,43,43);
bins[69]=sumbins(yL,44,44);
bins[70]=sumbins(yL,45,46);
bins[71]=sumbins(yL,47,47);
bins[72]=sumbins(yL,48,48);
bins[73]=sumbins(yL,49,50);
bins[74]=sumbins(yL,51,51);
bins[75]=sumbins(yL,52,53);
bins[76]=sumbins(yL,54,54);
bins[77]=sumbins(yL,55,56);
bins[78]=sumbins(yL,57,57);
bins[79]=sumbins(yL,58,59);
bins[80]=sumbins(yL,60,60);
bins[81]=sumbins(yL,61,62);
bins[82]=sumbins(yL,63,64);
bins[83]=sumbins(yL,65,66);
bins[84]=sumbins(yL,67,67);
bins[85]=sumbins(yL,68,69);
bins[86]=sumbins(yL,70,71);
bins[87]=sumbins(yL,72,73);
bins[88]=sumbins(yL,74,75);
bins[89]=sumbins(yL,76,77);
bins[90]=sumbins(yL,78,80);
bins[91]=sumbins(yL,81,82);
bins[92]=sumbins(yL,83,84);
bins[93]=sumbins(yL,85,87);
bins[94]=sumbins(yL,88,89);
bins[95]=sumbins(yL,90,91);
bins[96]=sumbins(yL,92,94);
bins[97]=sumbins(yL,95,97);
bins[98]=sumbins(yL,98,99);
bins[99]=sumbins(yL,100,102);
bins[100]=sumbins(yL,103,105);
bins[101]=sumbins(yL,106,108);
bins[102]=sumbins(yL,109,111);
bins[103]=sumbins(yL,112,114);
bins[104]=sumbins(yL,115,117);
bins[105]=sumbins(yL,118,121);
bins[106]=sumbins(yL,122,124);
bins[107]=sumbins(yL,125,128);
bins[108]=sumbins(yL,129,131);
bins[109]=sumbins(yL,132,135);
bins[110]=sumbins(yL,136,139);
bins[111]=sumbins(yL,140,143);
bins[112]=sumbins(yL,144,147);
bins[113]=sumbins(yL,148,151);
bins[114]=sumbins(yL,152,155);
bins[115]=sumbins(yL,156,159);
bins[116]=sumbins(yL,160,164);
bins[117]=sumbins(yL,165,168);
bins[118]=sumbins(yL,169,173);
bins[119]=sumbins(yL,174,178);
bins[120]=sumbins(yL,179,183);
bins[121]=sumbins(yL,184,188);
bins[122]=sumbins(yL,189,193);
bins[123]=sumbins(yL,194,199);
bins[124]=sumbins(yL,200,204);
bins[125]=sumbins(yL,205,210);
bins[126]=sumbins(yL,211,216);
bins[127]=sumbins(yL,217,222);
bins[128]=sumbins(yL,223,228);
bins[129]=sumbins(yL,229,235);
bins[130]=sumbins(yL,236,241);
bins[131]=sumbins(yL,242,248);
bins[132]=sumbins(yL,249,255);
bins[133]=sumbins(yL,256,262);
bins[134]=sumbins(yL,263,270);
bins[135]=sumbins(yL,271,277);
bins[136]=sumbins(yL,278,285);
bins[137]=sumbins(yL,286,293);
bins[138]=sumbins(yL,294,301);
bins[139]=sumbins(yL,302,310);
bins[140]=sumbins(yL,311,319);
bins[141]=sumbins(yL,320,328);
bins[142]=sumbins(yL,329,337);
bins[143]=sumbins(yL,338,346);
bins[144]=sumbins(yL,347,356);
bins[145]=sumbins(yL,357,366);
bins[146]=sumbins(yL,367,376);
bins[147]=sumbins(yL,377,387);
bins[148]=sumbins(yL,388,398);
bins[149]=sumbins(yL,399,409);
bins[150]=sumbins(yL,410,420);
bins[151]=sumbins(yL,421,432);
bins[152]=sumbins(yL,433,444);
bins[153]=sumbins(yL,445,457);
bins[154]=sumbins(yL,458,470);
bins[155]=sumbins(yL,471,483);
bins[156]=sumbins(yL,484,496);
bins[157]=sumbins(yL,497,510);
bins[158]=sumbins(yL,511,525);
bins[159]=sumbins(yL,526,539);
bins[160]=sumbins(yL,540,555);
bins[161]=sumbins(yL,556,570);
bins[162]=sumbins(yL,571,586);
bins[163]=sumbins(yL,587,603);
bins[164]=sumbins(yL,604,620);
bins[165]=sumbins(yL,621,637);
bins[166]=sumbins(yL,638,655);
bins[167]=sumbins(yL,656,673);
bins[168]=sumbins(yL,674,692);
bins[169]=sumbins(yL,693,712);
bins[170]=sumbins(yL,713,732);
bins[171]=sumbins(yL,733,752);
bins[172]=sumbins(yL,753,774);
bins[173]=sumbins(yL,775,795);
bins[174]=sumbins(yL,796,818);
bins[175]=sumbins(yL,819,841);
bins[176]=sumbins(yL,842,864);
bins[177]=sumbins(yL,865,889);
bins[178]=sumbins(yL,890,914);
bins[179]=sumbins(yL,915,939);
bins[180]=sumbins(yL,940,966);
bins[181]=sumbins(yL,967,993);
bins[182]=sumbins(yL,994,1021);
bins[183]=sumbins(yL,1022,1049);
bins[184]=sumbins(yL,1050,1079);
bins[185]=sumbins(yL,1080,1109);
bins[186]=sumbins(yL,1110,1140);
bins[187]=sumbins(yL,1141,1173);
bins[188]=sumbins(yL,1174,1205);
bins[189]=sumbins(yL,1206,1239);
bins[190]=sumbins(yL,1240,1274);
bins[191]=sumbins(yL,1275,1310);
bins[192]=sumbins(yL,1311,1347);
bins[193]=sumbins(yL,1348,1385);
bins[194]=sumbins(yL,1386,1424);
bins[195]=sumbins(yL,1425,1464);
bins[196]=sumbins(yL,1465,1505);
bins[197]=sumbins(yL,1506,1547);
bins[198]=sumbins(yL,1548,1591);
bins[199]=sumbins(yL,1592,1635);
bins[200]=sumbins(yL,1636,1681);
bins[201]=sumbins(yL,1682,1729);
bins[202]=sumbins(yL,1730,1777);
bins[203]=sumbins(yL,1778,1827);
bins[204]=sumbins(yL,1828,1879);
bins[205]=sumbins(yL,1880,1931);
bins[206]=sumbins(yL,1932,1986);
bins[207]=sumbins(yL,1987,2041);
bins[208]=sumbins(yL,2042,2099);
bins[209]=sumbins(yL,2100,2158);
bins[210]=sumbins(yL,2159,2219);
bins[211]=sumbins(yL,2220,2281);
bins[212]=sumbins(yL,2282,2345);
bins[213]=sumbins(yL,2346,2411);
bins[214]=sumbins(yL,2412,2479);
bins[215]=sumbins(yL,2480,2548);
bins[216]=sumbins(yL,2549,2620);
bins[217]=sumbins(yL,2621,2694);
bins[218]=sumbins(yL,2695,2769);
bins[219]=sumbins(yL,2770,2847);
bins[220]=sumbins(yL,2848,2927);
bins[221]=sumbins(yL,2928,3010);
bins[222]=sumbins(yL,3011,3094);
bins[223]=sumbins(yL,3095,3181);
bins[224]=sumbins(yL,3182,3271);
bins[225]=sumbins(yL,3272,3363);
bins[226]=sumbins(yL,3364,3457);
bins[227]=sumbins(yL,3458,3554);
bins[228]=sumbins(yL,3555,3654);
bins[229]=sumbins(yL,3655,3757);
bins[230]=sumbins(yL,3758,3863);
bins[231]=sumbins(yL,3864,3971);
bins[232]=sumbins(yL,3972,4083);
bins[233]=sumbins(yL,4084,4198);
bins[234]=sumbins(yL,4199,4316);
bins[235]=sumbins(yL,4317,4437);
bins[236]=sumbins(yL,4438,4562);
bins[237]=sumbins(yL,4563,4690);
bins[238]=sumbins(yL,4691,4822);
bins[239]=sumbins(yL,4823,4958);
bins[240]=sumbins(yL,4959,5097);
bins[241]=sumbins(yL,5098,5240);
bins[242]=sumbins(yL,5241,5388);
bins[243]=sumbins(yL,5389,5539);
bins[244]=sumbins(yL,5540,5695);
bins[245]=sumbins(yL,5696,5855);
bins[246]=sumbins(yL,5856,6019);
bins[247]=sumbins(yL,6020,6189);
bins[248]=sumbins(yL,6190,6363);
bins[249]=sumbins(yL,6364,6541);
bins[250]=sumbins(yL,6542,6725);
bins[251]=sumbins(yL,6726,6914);
bins[252]=sumbins(yL,6915,7109);
bins[253]=sumbins(yL,7110,7309);
bins[254]=sumbins(yL,7310,7514);
bins[255]=sumbins(yL,7515,7725);
bins[256]=sumbins(yL,7726,8191); //7943);
for (int i = 1; i <= maxbins; i++) {
	sumL=sumL+bins[i];
	if(bins[i]>maxL){maxL=bins[i];
//      	printf( "%d %f ", i,bins[i] );
}
	}
//bins[maxbins+2]=max(maxL,75.0);
bins[maxbins+2]=maxL;
      		fprintf(stderr, "%f %f ", sumL,bins[maxbins+2] );
}

char getMagnitudeChar(double magValue, double maxValue){
	//char* magnitudes="_.,-=~'";
	const char *magnitudes="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//return(magnitudes[(int)(magValue/maxValue*7.0)]);
	return(magnitudes[(int)(magValue/maxValue*36.0)]);
}



int doFFT(int startbuffer, char *buffer[], Canvas *canvas)
{
	//fftw_complex xL[N];
	//fftw_complex xR[N];
	//fftw_complex yL[N];
	//fftw_complex yR[N];
	//double mL[N];
	//double mR[N];
	double binsL[maxbins+3];
	double binsR[maxbins+3];
	short tempL;
	short tempR;
	int bufnum;
	int cursor;
	for (int i = 0; i < N; i++) {
      		bufnum=(startbuffer+(i/buffer_frames))%buffers;
      		cursor= i%buffer_frames ;
		tempL = (short)((unsigned int)buffer[bufnum][cursor*4]| (unsigned int)buffer[bufnum][cursor*4+1]<<8);
		tempR = (short)((unsigned int)buffer[bufnum][cursor*4+2]| (unsigned int)buffer[bufnum][cursor*4+3]<<8);
		xL[i][REAL] = window[i]*((double)tempL/32768.0);
		xR[i][REAL] = window[i]*((double)tempR/32768.0);
		xL[i][IMAG] = 0;
		xR[i][IMAG] = 0;
	}
	// compute the FFT of x and store the results in y
	//fft(xL, yL);
	//fft(xR, yR);
	fftw_execute(Lplan);
	fftw_execute(Rplan);
	for (int i = 0; i < N/2; i++) {
		mL[i]=sqrt(yL[i][IMAG]*yL[i][IMAG]+yL[i][REAL]*yL[i][REAL]);
		mR[i]=sqrt(yR[i][IMAG]*yR[i][IMAG]+yR[i][REAL]*yR[i][REAL]);
		}
	//for (int i = 0; i < N; i++) {
	//	mL[i]=sqrt(mL[i]);
	//	mR[i]=sqrt(mR[i]);
      	//	//printf( "f(%f,%f) ",  mL[i],mR[i] );
	//	}

      		//printf( "%f - ", mL[0] );
	makebins(binsL,mL);
      		//printf( "%f - ", mR[0] );
	makebins(binsR,mR);
	CurrentPanelBin=(CurrentPanelBin+1)%64;
	for (int i=0;i<maxbins+3;i++){
		PanelBinsL[CurrentPanelBin][i]=binsL[i];
		PanelBinsR[CurrentPanelBin][i]=binsR[i];
		}
	//updatePanel(binsL,binsR,canvas);
    return 0;
}
int main (int argc, char *argv[])
{
  int i=0; //,buff_i,j;
  //short * sampleLP;
  //short * sampleRP;
  int err;
  char *buffer[buffers];
  const char *arg="hw:1,0";
  unsigned int rate = 48000;
  snd_pcm_t *capture_handle;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_sframes_t avail_cap;
  RGBMatrix::Options defaults;
  defaults.hardware_mapping="adafruit-hat-pwm";
  defaults.rows=64;
  defaults.cols=256;
  defaults.chain_length=1;
  defaults.row_address_type=4;
  defaults.panel_type="fm6127";  
  snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

  setupPanelBins();
  makeWindow();

  if ((err = snd_pcm_open (&capture_handle, arg, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
    fprintf (stderr, "cannot open audio device %s (%s)\n", 
             arg,
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "audio interface opened\n");
		   
  if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
    fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params allocated\n");
			 
  if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
    fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params initialized\n");
	
  if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    fprintf (stderr, "cannot set access type (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params access setted\n");
	
  if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, format)) < 0) {
    fprintf (stderr, "cannot set sample format (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params format setted\n");
	
  if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
    fprintf (stderr, "cannot set sample rate (%s)\n",
             snd_strerror (err));
    exit (1);
  }
	
  fprintf(stderr, "hw_params rate setted\n");

  if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params,2)) < 0) {
    fprintf (stderr, "cannot set channel count (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params channels setted\n");
	
  if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
    fprintf (stderr, "cannot set parameters (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "hw_params setted\n");
	
  snd_pcm_hw_params_free (hw_params);

  fprintf(stderr, "hw_params freed\n");
	
  if ((err = snd_pcm_prepare (capture_handle)) < 0) {
    fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stderr, "audio interface prepared\n");

  Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  image_gen = new updatePanel(canvas);
  image_gen->Start();

  fprintf(stderr, "buffer allocated\n");

  for (i = 0; i < buffers; ++i) {
  buffer[i] = (char *)malloc(buffer_frames * snd_pcm_format_width(format) / 8 * 2);
    if ((err = snd_pcm_readi (capture_handle, buffer[i], buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
      exit (1);
    }
  }
  while( !interrupt_received) {
	i++;
	i=i%buffers;
    avail_cap = snd_pcm_avail ( capture_handle  );
    
    fprintf (stderr,"snd_pcm_avail: %ld \n", (avail_cap=snd_pcm_avail_update( capture_handle  ))  );
    //avail_cap=snd_pcm_avail_update( capture_handle);

    if ((err = snd_pcm_readi (capture_handle, buffer[i], buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
      exit (1);
    }
	while (snd_pcm_avail_update( capture_handle) > buffer_frames){
    		snd_pcm_readi (capture_handle, buffer[i], buffer_frames);
    printf( " DROP \n");

}

//    printf( "%s\n",buffer[i]);
    doFFT(i,buffer,canvas);
    //printf( "\n");
  }

  free(buffer[0]);

  fprintf(stderr, "buffer freed\n");
	
  snd_pcm_close (capture_handle);
  fprintf(stderr, "audio interface closed\n");
  fftw_destroy_plan(Lplan);
  fftw_destroy_plan(Rplan);
  fftw_cleanup();

  canvas->Clear();
  delete image_gen;
  delete canvas;
  exit (0);
}

