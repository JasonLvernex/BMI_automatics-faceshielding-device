#ifndef __MYFEATURE_H
#define __MYFEATURE_H
#include "sys.h"
#include "delay.h"
#include "adc.h"
#define DATASIZE 10

	float FFMN(float binned_signal[DATASIZE]);
	float FFMD(float binned_signal[DATASIZE]);
	int flag_label(float binned_signal[DATASIZE]);
	float MFMD(float binned_signal[DATASIZE]);
  float MFMN(float binned_signal[DATASIZE]);
	float *fft_trans(float binned_signal[DATASIZE]);
	float MMAV1(float binned_signal[DATASIZE]);
	float MMAV2(float binned_signal[DATASIZE]);
	float MAV(float binned_signal[DATASIZE]);
	float SSI(float binned_signal[DATASIZE]);
	float WAMP(float binned_signal[DATASIZE], float threshold);
	float WL(float binned_signal[DATASIZE]);
	float ZC(float binned_signal[DATASIZE],float threshold, float variance);
	float FR(float binned_signal[DATASIZE]);
	float IEMG(float binned_signal[DATASIZE]);
	float VAR(float binned_signal[DATASIZE]);
	float SSC(float binned_signal[DATASIZE],float threshold);
	float RMS(float binned_signal[DATASIZE]);
 //float dft(float data[DATASIZE]);



				    
#endif
