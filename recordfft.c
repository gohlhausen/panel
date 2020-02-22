/* 
  alsa-record-example.c
  pcm_i.c
  A Minimal Capture Program

  This program opens an audio interface for capture, configures it for
  stereo, 16 bit, 44.1kHz, interleaved conventional read/write
  access. Then its reads a chunk of random data from it, and exits. It
  isn't meant to be a real program.

  From on Paul David's tutorial : http://equalarea.com/paul/alsa-audio.html

  Fixes rate and buffer problems

  sudo apt-get install libasound2-dev
  gcc -o alsa-record-example -lasound alsa-record-example.c && ./alsa-record-example hw:0
  gcc -o alsa-record-example -lasound alsa-record-example.c && ./alsa-record-example plughw:1,0

  gcc -o alsa-record-example  alsa-record-example.c -lasound
  
  gcc -o pcm_i -lasound pcm_i.c && ./pcm_i plughw:1,0
  
  
  gbookFsrf08.js
  gbF( 'srf08','t@pi','Mon Feb 10 22:10:41 UTC 2014','127.0.0.1',10,0,143,0,'comments');

*/

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <fftw3.h>
void Spectrogram(){
    int transform_size = 1024;
    int half = transform_size/2;
    int step_size = transform_size/2;
    double in[transform_size];
    double processed[half];
    fftw_complex *out;
    fftw_plan p;

    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * transform_size);


    for (int x=0; x < wavFile->getSamples()/step_size; x++) {

        // Fill the transformation array with a sample frame and apply the window function.
        // Normalization is performed later
        // (One error was here: you didn't set the last value of the array in)
        for (int j = 0, int i = x * step_size; i < x * step_size + transform_size; i++, j++)
            in[j] = wavFile->getSample(i) * windowHanning(j, transform_size);

        p = fftw_plan_dft_r2c_1d(transform_size, in, out, FFTW_ESTIMATE);

        fftw_execute(p); /* repeat as needed */

        for (int i=0; i < half; i++) {
            // (Here were some flaws concerning the access of the complex values)
            out[i][0] *= (2./transform_size);                         // real values
            out[i][1] *= (2./transform_size);                         // complex values
            processed[i] = out[i][0]*out[i][0] + out[i][1]*out[i][1]; // power spectrum
            processed[i] = 10./log(10.) * log(processed[i] + 1e-6);   // dB

            // The resulting spectral values in 'processed' are in dB and related to a maximum
            // value of about 96dB. Normalization to a value range between 0 and 1 can be done
            // in several ways. I would suggest to set values below 0dB to 0dB and divide by 96dB:

            // Transform all dB values to a range between 0 and 1:
            if (processed[i] <= 0) {
                processed[i] = 0;
            } else {
                processed[i] /= 96.;             // Reduce the divisor if you prefer darker peaks
                if (processed[i] > 1)
                    processed[i] = 1;
            }

//In->setPixel(x,(half-1)-i,processed[i]*255);
        }

        // This should be called each time fftw_plan_dft_r2c_1d()
        // was called to avoid a memory leak:
        fftw_destroy_plan(p);
    }

    fftw_free(out);
}
	      
main (int argc, char *argv[])
{
  int i,buff_i,j;
  short * sampleLP;
  short * sampleRP;

  int err;
  char *buffer;
  char *arg="hw:1";
  int buffer_frames = 128;
  unsigned int rate = 48000;
  snd_pcm_t *capture_handle;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_sframes_t avail_cap;
  
  snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

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

  buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

  fprintf(stderr, "buffer allocated\n");

  for (i = 0; i < 10; ++i) {
    avail_cap = snd_pcm_avail ( capture_handle  );
    
    fprintf (stderr,"snd_pcm_avail: %d ", (avail_cap=snd_pcm_avail_update( capture_handle  ))  );

    if ((err = snd_pcm_readi (capture_handle, buffer, buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
      exit (1);
    }

    for (j = 0; j < 128; j+=2) {
      
      sampleLP = ( short * )(&buffer[j]   );
      sampleRP = ( short * )(&buffer[j+1] );
      printf( "f(%d,%d,0,0)\n", ( int ) (sampleLP[0]) ,  ( int )( sampleRP[0] ) );
 
      //printf( "f(%d,%d,0,0)\n", buffer[j], buffer[j+1]);
 
 
    }  
    printf( "\n");
  }

  free(buffer);

  fprintf(stderr, "buffer freed\n");
	
  snd_pcm_close (capture_handle);
  fprintf(stderr, "audio interface closed\n");

  exit (0);
}

