#ifndef __Algorithm_filter_H
#define	__Algorithm_filter_H

#include "ALL_DEFINE.h"
#include "myMath.h"


/*  LPF 1st filter   */
typedef struct{
		float old_data;
		float new_data;
		float factor;
}Filter_LPF_1;
extern float LPF_1_Filter_1(Filter_LPF_1 *LPF_1);
extern float LPF_1_Filter_2(Filter_LPF_1 *LPF_1,float dt);


typedef struct {
	u16 cnt;
	u16 input;
	u16 *average;
	u8  max_cnt;
}MovAverage;

extern u16 AntiPulse_MovingAverage_Filter(MovAverage *_MovAverage);
extern u16 MovingAverage_Filter(MovAverage *_MovAverage);


extern float IIR_I_Filter(float InData, float *x, float *y,  const float *b, u8 nb, const float *a, u8 na);

extern void Moving_Average(float in,float moavarray[],u16 len ,u16 fil_cnt[2],float *out);
extern float  Moving_Median(u8 item,u8 width_num,float in);
//------------------------------------------------------
void LPF2pSetCutoffFreq_1(float sample_freq, float cutoff_freq);
float LPF2pApply_1(float sample);
void LPF2pSetCutoffFreq_2(float sample_freq, float cutoff_freq);
float LPF2pApply_2(float sample);
void LPF2pSetCutoffFreq_3(float sample_freq, float cutoff_freq);
float LPF2pApply_3(float sample);
#endif /* __Algorithm_filter_H */
