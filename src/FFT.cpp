#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
float * fft_vector = NULL;
int fft_vector_size = 0;

vector<pair<double,double> > FFT(vector<double> & signal, unsigned int sample_rate, int sign) {
  unsigned long n,mmax,m,j,istep,i;
  double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;

  //the complex array is real+complex so the array
  //as a size n = 2* number of complex samples
  //real part is the data[index] and
  //the complex part is the data[index+1]
  if ((unsigned int) fft_vector_size < (2*sample_rate)) {
    if (fft_vector != NULL)
      delete [] fft_vector;
    fft_vector = new float [2*sample_rate];
    fft_vector_size = 2*sample_rate;
  }

  //put the real array in a complex array
  //the complex part is filled with 0's
  //the remaining vector with no data is filled with 0's
  for(n=0; n<sample_rate; n++) {
    if (n < signal.size())
      fft_vector[2*n] = (float) signal[n];
    else fft_vector[2*n] = 0;
    fft_vector[2*n+1] = 0;
  }

  //binary inversion (note that the indexes
  //start from 0 witch means that the
  //real part of the complex is on the even-indexes
  //and the complex part is on the odd-indexes)
  n = sample_rate << 1;
  j=0;
  for (i=0;i<n/2;i+=2) {
    if (j > i) {
      SWAP(fft_vector[j],fft_vector[i]);
      SWAP(fft_vector[j+1],fft_vector[i+1]);
      if((j/2)<(n/4)){
	SWAP(fft_vector[(n-(i+2))],fft_vector[(n-(j+2))]);
	SWAP(fft_vector[(n-(i+2))+1],fft_vector[(n-(j+2))+1]);
      }
    }
    m = n >> 1;
    while (m >= 2 && j >= m) {
      j -= m;
      m >>= 1;
    }
    j += m;
  }

  // Danielson-Lanzcos routine
  mmax = 2;
  while (n > mmax) {
    istep = mmax << 1;
    theta = sign*(2*M_PI/mmax);
    wtemp = sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (m=1;m<mmax;m+=2) {
      for (i=m;i<=n;i+=istep) {
	j = i + mmax;
	tempr = wr*fft_vector[j-1]-wi*fft_vector[j];
	tempi = wr*fft_vector[j]+wi*fft_vector[j-1];
	fft_vector[j-1] = fft_vector[i-1]-tempr;
	fft_vector[j] = fft_vector[i]-tempi;
	fft_vector[i-1] += tempr;
	fft_vector[i] += tempi;
      }
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
    }
    mmax=istep;
  }

  vector<pair<double, double> > result;
  for(i=2; i < 2*sample_rate; i+=2){
    result.push_back(pair<double, double>((double)fft_vector[i],(double)fft_vector[i+1]));
  }
  return result;
}


std::vector<std::pair<double,double> > windowedFFT(
    const std::vector<double>& sensorValues, size_t startIndex, size_t endIndex,
    int sample_rate, int sign) 
{
    std::vector<double> walkValues;
    for (size_t i=startIndex;i<=endIndex;i++) {
        walkValues.push_back(sensorValues[i]);
    }

    return FFT(walkValues, sample_rate, sign);
}

/*****************************************************************************/

void test_fft() {

  cout << "-----------------------------------\n";
  cout << "FFT Test Suite\n";
  cout << "-----------------------------------\n";
  cout << "FFT computation with noise.";

  //sample rate of the signal (must be 2^n)
  long sample_rate=8192;

  //number of samples you want to send for processing in the fft (any)
  //for example 100 samples
  long captured_samples=500;

  //frequency of the signal (has to be smaller than sample_rate/2)
  //for example 46
  int frequency=250;

  vector<double> signal;

  for(int i=0; i<captured_samples; i++) {
    double temp1, temp2;
    temp1=(double)(2 * M_PI * frequency * ((float)i/sample_rate));
    temp2=(double)(2 * M_PI * (10*frequency) * ((float)i/sample_rate));
    signal.push_back(30 * sin(temp1) + 10 * sin(temp2) +(i%3-1)*0.1);
  }

  vector<pair<double,double> > result = FFT(signal, sample_rate, 1);
}


/*****************************************************************************/

