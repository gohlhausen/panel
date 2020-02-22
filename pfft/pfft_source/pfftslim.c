/*
  Copyright (c) 2013 Julien Pommier.

  Small test & bench for PFFFT, comparing its performance with the scalar FFTPACK, FFTW, and Apple vDSP

  How to build: 

   gcc -O3  -ffast-math pfftslim.c pffft.c -o pfftslim fftpack.c -lm -I/usr/local/include/ -L/usr/local/lib/ -lfftw3f


 */

#include "pffft.h"
#include "fftpack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#ifdef HAVE_SYS_TIMES
#  include <sys/times.h>
#  include <unistd.h>
#endif

#ifdef HAVE_VECLIB
#  include <Accelerate/Accelerate.h>
#endif

#ifdef HAVE_FFTW
#  include <fftw3.h>
#endif

#define MAX(x,y) ((x)>(y)?(x):(y))

double frand() {
  return rand()/(double)RAND_MAX;
}

#if defined(HAVE_SYS_TIMES)
  inline double uclock_sec(void) {
    static double ttclk = 0.;
    if (ttclk == 0.) ttclk = sysconf(_SC_CLK_TCK);
    struct tms t; return ((double)times(&t)) / ttclk;
  }
# else
  double uclock_sec(void)
{ return (double)clock()/(double)CLOCKS_PER_SEC; }
#endif



int array_output_format = 0;

void show_output(const char *name, int N, int cplx, float flops, float t0, float t1, int max_iter) {
  float mflops = flops/1e6/(t1 - t0 + 1e-16);
  if (array_output_format) {
    if (flops != -1) {
      printf("|%9.0f   ", mflops);
    } else printf("|      n/a   ");
  } else {
    if (flops != -1) {
      printf("N=%5d, %s %16s : %6.0f MFlops [t=%6.0f ns, %d runs]\n", N, (cplx?"CPLX":"REAL"), name, mflops, (t1-t0)/2/max_iter * 1e9, max_iter);
    }
  }
  fflush(stdout);
}

void benchmark_ffts(int N, int cplx) {
  int Nfloat = (cplx ? N*2 : N);
  int Nbytes = Nfloat * sizeof(float);
  float *X = pffft_aligned_malloc(Nbytes), *Y = pffft_aligned_malloc(Nbytes), *Z = pffft_aligned_malloc(Nbytes);

  double t0, t1, flops;

  int k;
  int max_iter = 5120000/N*4;
#ifdef __arm__
  max_iter /= 4;
#endif
  int iter;

  for (k = 0; k < Nfloat; ++k) {
    X[k] = 0; //sqrtf(k+1);
  }


  // PFFFT benchmark
  {
    PFFFT_Setup *s = pffft_new_setup(N, cplx ? PFFFT_COMPLEX : PFFFT_REAL);
    if (s) {
      t0 = uclock_sec();  
      for (iter = 0; iter < max_iter; ++iter) {
        pffft_transform(s, X, Z, Y, PFFFT_FORWARD);
        pffft_transform(s, X, Z, Y, PFFFT_BACKWARD);
      }
      t1 = uclock_sec();
      pffft_destroy_setup(s);
    
      flops = (max_iter*2) * ((cplx ? 5 : 2.5)*N*log((double)N)/M_LN2); // see http://www.fftw.org/speed/method.html
      show_output("PFFFT", N, cplx, flops, t0, t1, max_iter);
    }
  }


  pffft_aligned_free(X);
  pffft_aligned_free(Y);
  pffft_aligned_free(Z);
}

#ifndef PFFFT_SIMD_DISABLE
void validate_pffft_simd(); // a small function inside pffft.c that will detect compiler bugs with respect to simd instruction 
#endif

int main(int argc, char **argv) {
  int Nvalues[] = { 4096, 8192, 16384, 32768, -1 };
  int i;

  if (argc > 1 && strcmp(argv[1], "--array-format") == 0) {
    array_output_format = 1;
  }

  if (!array_output_format) {
    for (i=0; Nvalues[i] > 0; ++i) {
      benchmark_ffts(Nvalues[i], 0 /* real fft */);
    }
  }


  return 0;
}
