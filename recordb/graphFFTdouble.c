
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <fftw3.h>
	      
// macros for the real and imaginary parts
#define REAL 0
#define IMAG 1
#define N 16384
#define buffers 16
#define buffer_frames 1024

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

int doFFT(int startbuffer, char *buffer[])
{
	fftw_complex xL[N];
	fftw_complex xR[N];
	fftw_complex yL[N];
	fftw_complex yR[N];
	double * tempL;
	double * tempR;
	int bufnum;
	int cursor;
	for (int i = 0; i < N; i++) {
      		bufnum=(startbuffer+(i/buffer_frames))%buffers;
      		cursor= i%buffer_frames ;
      		//printf( "f(%d,%d,0,0)\n",  bufnum,cursor );
		tempL = (double *)(&buffer[bufnum][cursor*16]);
		tempR = (double *)(&buffer[bufnum][cursor*16+8]);
      		//printf( "f(%d,%d,%f,%f)\n",  bufnum,cursor,*tempL,*tempR );
		xL[i][REAL] = *tempL;
		xR[i][REAL] = *tempR;
		xL[i][IMAG] = 0;
		xR[i][IMAG] = 0;
	}
	// compute the FFT of x and store the results in y
	fft(xL, yL);
	fft(xR, yR);
      	printf( "L(%f) R(%f)\n",  getMagnitude(yL[0]),getMagnitude(yR[0]));
	printf( "L(%f) R(%f)\n",  getMagnitude(yL[170]),getMagnitude(yR[170]));
      	printf( "L(%f) R(%f)\n",  getMagnitude(yL[1700]),getMagnitude(yR[1700]));
      	printf( "L(%f) R(%f)\n",  getMagnitude(yL[30]),getMagnitude(yR[30]));
      	printf( "L(%f) R(%f)\n\n",  getMagnitude(yL[40]),getMagnitude(yR[40]));
    return 0;
}
void main (int argc, char *argv[])
{
  int i,buff_i,j;
  short * sampleLP;
  short * sampleRP;
  int err;
  char *buffer[buffers];
  char *arg="default:audioinjectorpi";
  unsigned int rate = 96000;
  snd_pcm_t *capture_handle;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_sframes_t avail_cap;
  
  snd_pcm_format_t format = SND_PCM_FORMAT_FLOAT64_LE;

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


  fprintf(stderr, "buffer allocated\n");

  for (i = 0; i < buffers; ++i) {
  buffer[i] = malloc(buffer_frames * snd_pcm_format_width(format) / 8 * 2);
    if ((err = snd_pcm_readi (capture_handle, buffer[i], buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
      exit (1);
    }
  }
  for (i = 0; i < 3200; ++i) {
    avail_cap = snd_pcm_avail ( capture_handle  );
    
    fprintf (stderr,"snd_pcm_avail: %ld ", (avail_cap=snd_pcm_avail_update( capture_handle  ))  );

    if ((err = snd_pcm_readi (capture_handle, buffer[i%buffers], buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
      exit (1);
    }

    doFFT(i%buffers,buffer);
    printf( "\n");
  }

  free(buffer[0]);

  fprintf(stderr, "buffer freed\n");
	
  snd_pcm_close (capture_handle);
  fprintf(stderr, "audio interface closed\n");

  exit (0);
}

