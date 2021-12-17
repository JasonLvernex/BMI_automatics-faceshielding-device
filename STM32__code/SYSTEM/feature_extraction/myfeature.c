/**
*Acknowledgement
*this is the feature extraction toolbox create by Jason Lyu
*01/12/2021 Beijing Institute of Technology
**/


#include "myfeature.h"
#include <stdio.h>
#include <math.h>
#include "arm_math.h"

#define FFT_LEN	64  //采样率
#define FFT_DS 1024
static float fft_intputbuf[FFT_LEN];//FFT_LEN*2
static float fft_outputbuf[FFT_LEN];

#define DATASIZE 10
#define DELTA 0.00002   // ????????
#define Fs 1000 //采样率 1000 频率分辨率 5Hz


	

/**
  * @brief  Fourier transformation with high computation.
  * @param  data[DATASIZE]: the data sampled
  */
/*float dft(float data[DATASIZE])
	{
  // const int N = sizeof data /sizeof data[0];
  int N = DATASIZE;
  float result[N];
  for(int k=0; k <= N/2-1; ++k) {
    float Re=0;
    float Im=0;
    for(int n=0; n<N; ++n) {
      float tht = 2*PI*k*n/N;
      Re += data[n] * cos(tht);
      Im += data[n] * sin(tht);
      // printf("Re(%d): %f\n", n,Re);
    }// i
    Re = pow(Re, 2.0);
    Im = pow(Im, 2.0);
    float delta;
    delta = pow(DELTA, 2.0);
    data[k] = delta*(Re+Im);
    // printf("%d, %e\n", k, result[k]);
  }// j
}*/
float *fft_trans(float binned_signal[FFT_LEN])
{
		arm_cfft_radix4_instance_f32 scfft;
	int i;
	//*fft_outputbuf=*fft_outputbuf-64;
	for (i=0;i<FFT_LEN;i++){fft_outputbuf[i]=0;}
	
			  for (i=0;i<FFT_LEN;i++){fft_intputbuf[i]=binned_signal[i];}
			arm_cfft_radix4_init_f32(&scfft,FFT_LEN,0,1);
		/*			for(i=0;i<FFT_LEN;i++)
			{
				fft_intputbuf[2*i]=100+ 10*arm_sin_f32(2*PI*i/Fs)+
										30*arm_sin_f32(2*PI*i*4/Fs)+
										50*arm_sin_f32(2*PI*i*8/Fs);
				fft_intputbuf[2*i+1]=0;
			}*/
			
		arm_cfft_radix4_f32(&scfft,fft_intputbuf);//FFT计算
		arm_cmplx_mag_f32(fft_intputbuf,fft_outputbuf,FFT_LEN);
 return fft_outputbuf;
			
}



/**
  * @brief  Frequency Mean (FMN).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The FMN of the Bin
  */
	float FFMN(float binned_signal[FFT_LEN])
	{
		int i;
		float ans=0,psd[64],ans1=0,ans2=0;
	//**	  for (i=0;i<FFT_LEN;i++){fft_intputbuf[i]=binned_signal[i];}
	//**	arm_cfft_radix4_init_f32(&scfft,FFT_LEN,0,1);
		/*			for(i=0;i<FFT_LEN;i++)
			{
				fft_intputbuf[2*i]=100+ 10*arm_sin_f32(2*PI*i/Fs)+
										30*arm_sin_f32(2*PI*i*4/Fs)+
										50*arm_sin_f32(2*PI*i*8/Fs);
				fft_intputbuf[2*i+1]=0;
			}*/
			
	//**	arm_cfft_radix4_f32(&scfft,fft_intputbuf);//FFT计算
	//**	arm_cmplx_mag_f32(fft_intputbuf,fft_outputbuf,FFT_LEN);
			//printf("FFT Result:\t\n");
		/*	for(i=0;i<FFT_LEN;i++)
			{
				printf("fft_outbuf[%d]:%f\r\n",i,fft_outputbuf[i]);
			}*/
			
			
			//PSD calculation
			for(i=0;i<FFT_LEN;i++)
			{
				psd[i]=pow(fabs(binned_signal[i]),2);
			}
			for(i=0;i<FFT_LEN;i++)
			{
				ans1=ans1+(i*FFT_LEN*psd[i]);
			}
			for(i=0;i<FFT_LEN;i++)
			{
				ans2=ans2+psd[i];
			}
			if(ans2==0) ans2=1;
			ans=ans1/ans2;
		return ans;
	}
	
	
	
	
	/**
  * @brief  Frequency Median (FMD).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The FMD of the Bin
  */
		float FFMD(float binned_signal[FFT_LEN])
	{
				int i;
		float ans=0,psd[64],ans2=0;
		//**	  for (i=0;i<FFT_LEN;i++){fft_intputbuf[i]=binned_signal[i];}
		//**		arm_cfft_radix4_init_f32(&scfft,FFT_LEN,0,1);
		/*			for(i=0;i<FFT_LEN;i++)
			{
				fft_intputbuf[2*i]=100+ 10*arm_sin_f32(2*PI*i/Fs)+
										30*arm_sin_f32(2*PI*i*4/Fs)+
										50*arm_sin_f32(2*PI*i*8/Fs);
				fft_intputbuf[2*i+1]=0;
			}*/
			
		//**	arm_cfft_radix4_f32(&scfft,fft_intputbuf);//FFT计算
		//**	arm_cmplx_mag_f32(fft_intputbuf,fft_outputbuf,FFT_LEN);
			//PSD calculation
			for(i=0;i<FFT_LEN;i++)
			{
				psd[i]=pow(fabs(binned_signal[i]),2);
			}
	    for(i=0;i<FFT_LEN;i++)
			{
				ans2=ans2+psd[i];
			}
			ans=0.5*ans2;
		return ans;
	}
	
	
	
	
	/**
  * @brief  flag_label.
  * @param  the flag labeling of the data
  * @retval flaging of the window
  */
int flag_label(float binned_signal[FFT_LEN])
{
	int ans=0;
	int i;
	for(i=0;i<FFT_LEN;i++)
	{
		ans=binned_signal[i]+ans;
	}
	if (ans>=3) ans=1;
	else ans=0;
	return ans;
}
	
	
	
	
	/**
  * @brief  Modified Frequency Median (MFMD).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The MFMD of the Bin
  */
	float MFMD(float binned_signal[FFT_LEN])
{
	//int NX[FFT_LEN];
		int i;
	
	/*for(i=0;i<FFT_LEN;i++)
	{
	NX[i] = (int)pow(2, floor( log(binned_signal[i])/log((float)2) ));//nextpow2
	}*/
		float ans=0;
	//**	  for (i=0;i<FFT_LEN;i++){fft_intputbuf[i]=binned_signal[i];}
	//**		arm_cfft_radix4_init_f32(&scfft,FFT_LEN,0,1);
	/*				for(i=0;i<FFT_LEN;i++)
			{
				fft_intputbuf[2*i]=100+ 10*arm_sin_f32(2*PI*i/Fs)+
										30*arm_sin_f32(2*PI*i*4/Fs)+
										50*arm_sin_f32(2*PI*i*8/Fs);
				fft_intputbuf[2*i+1]=0;
			}*/
			
//**		arm_cfft_radix4_f32(&scfft,fft_intputbuf);//FFT计算
//**		arm_cmplx_mag_f32(fft_intputbuf,fft_outputbuf,FFT_LEN);
			    for(i=0;i<FFT_LEN;i++)
			{
				ans=ans+binned_signal[i];
			}
			return ans;
		
}

	/**
  * @brief  Modified Frequency Mean (MFMN).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The MFMD of the Bin
  */
	float MFMN(float binned_signal[FFT_LEN])
{
//	int NX[FFT_LEN];
	int i;
	
	/*for(i=0;i<FFT_LEN;i++)
	{
	NX[i] = (int)pow(2, floor( log(binned_signal[i])/log((float)2) ));//nextpow2
	}*/
		float ans=0,ans1=0,ans2=0;
//**		  for (i=0;i<FFT_LEN;i++){fft_intputbuf[i]=binned_signal[i];}
	//**		arm_cfft_radix4_init_f32(&scfft,FFT_LEN,0,1);
		/*			for(i=0;i<FFT_LEN;i++)
			{
				fft_intputbuf[2*i]=100+ 10*arm_sin_f32(2*PI*i/Fs)+
										30*arm_sin_f32(2*PI*i*4/Fs)+
										50*arm_sin_f32(2*PI*i*8/Fs);
				fft_intputbuf[2*i+1]=0;
			}*/
			
//**		arm_cfft_radix4_f32(&scfft,fft_intputbuf);//FFT计算
//**		arm_cmplx_mag_f32(fft_intputbuf,fft_outputbuf,FFT_LEN);
						for(i=0;i<FFT_LEN;i++)
			{
				ans1=ans1+(i*FFT_LEN*binned_signal[i]);
			}
									for(i=0;i<FFT_LEN;i++)
			{
				ans2=ans2+binned_signal[i];
			}
			if(ans2==0) ans2=1;
			ans=ans1/ans2;
			return ans;	
}

	/**
  * @brief  Frequency Ratio (FR).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The FR of the Bin
  */
float findmax(float a[FFT_LEN]) 
{
	int i;
	float max;
	max=a[0];
	for(i=0;i<FFT_LEN;i++)
	{
		max=fmax(a[i],max);
	}

return max;
}


float findmin(float a[FFT_LEN]) 
{
	int i;
	float min;
	min=a[0];
	for(i=0;i<FFT_LEN;i++)
	{
		min=fmin(a[i],min);
	}

return min;
}


	float FR(float binned_signal[FFT_LEN])
{
	int i;
	float min,max,ans,buff[FFT_LEN];
	//fft_trans(binned_signal);
		for(i=0;i<FFT_LEN;i++)
	{
		buff[i]=binned_signal[i];
	}
	max=findmax(buff);
	min=findmin(buff);
	if(max==0) max=1;
	ans=min/max;
	return ans;
}

	/**
  * @brief  Modified Mean Absolute Value 1 (MMAV1).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The MMAV1 of the Bin
  */
float weight1(int i, int n)
{ float w;
	n=FFT_LEN;
	if (i>0.25*n && i<0.75*n) w=1;
	else w=0.5;
	return w;
}
	float MMAV1(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN;i++)
	{
		ans=fabs(binned_signal[i])*weight1(i,FFT_LEN)+ans;
	}
	ans=ans/FFT_LEN;
	return ans;
}

	/**
  * @brief  Modified Mean Absolute Value 2 (MMAV2).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The MMAV2 of the Bin
  */
float weight2(int i, int n)
{ float w;
	n=FFT_LEN;
	if (i>=0.25*n && i<=0.75*n) w=1;
	if (i<0.25*n) w=(4*i)/n;
	if (i>0.75*n) w=(4*(i-n))/n;
	return w;
}
	float MMAV2(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN;i++)
	{
		ans=fabs(binned_signal[i])*weight2(i,FFT_LEN)+ans;
	}
	ans=ans/FFT_LEN;
	return ans;
}

	/**
  * @brief  Modified Mean Absolute Value  (MAV).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The MAV of the Bin
  */
	float MAV(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN;i++)
	{
		ans=fabs(binned_signal[i])+ans;
	}
	ans=ans/FFT_LEN;
	return ans;
}

	/**
  * @brief  Simple Square Integral  (SSI).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The SSI of the Bin
  */
	float SSI(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN;i++)
	{
		ans=fabs(pow(binned_signal[i],2))+ans;
	}
	return ans;
}

	/**
  * @brief  Willison Amplitude  (WAMP).
  * @param  binned_signal[FFT_LEN]: binned data
  * @param  threshold of the WAMP
  * @retval The WAMP of the Bin
  */
  float f_WAMP(float indata, float threshold)
{
	float ans=0;
	if (indata>threshold) ans=1;
	else ans=0;
	return ans;
}
	float WAMP(float binned_signal[FFT_LEN], float threshold)
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN-1;i++)
	{
		ans=f_WAMP(fabs(binned_signal[i]-binned_signal[i+1]),threshold)+ans;
	}
	return ans;
}

	/**
  * @brief  Waveform Length  (WL).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The WL of the Bin
  */
	float WL(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN-1;i++)
	{
		ans=fabs(binned_signal[i]-binned_signal[i+1])+ans;
	}
	return ans;
}

	/**
  * @brief  Zero Crossings  (ZC).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The ZC of the Bin
  */
	float ZC(float binned_signal[FFT_LEN],float threshold, float variance)
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN-1;i++)
	{
		if((binned_signal[i]>threshold && binned_signal[i+1]<threshold)||(binned_signal[i]<threshold && binned_signal[i+1]>threshold))
		{
			if (fabs(binned_signal[i]-binned_signal[i+1])>=variance) ans++;
		}
	}
	return ans;
}

	/**
  * @brief  Integrated EMG  (IEMG).
  * summation of the absolute values of EMG signals
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The IEMG of the Bin
  */
	float IEMG(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;
		for(i=0;i<FFT_LEN;i++)
	{
   ans=ans+fabs(binned_signal[i]);
	}
	return ans;
}

	/**
  * @brief  Variance (VAR).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The VAR of the Bin
  */
	float VAR(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0,sum=0;
		for(i=0;i<FFT_LEN;i++)
	{
   sum=sum+binned_signal[i];
	}
	sum=sum/FFT_LEN;
			for(i=0;i<FFT_LEN;i++)
	{
   ans=ans+pow(binned_signal[i]-sum,2);
	}
	ans=ans/FFT_LEN;
	return ans;
}

	/**
  * @brief  Slope Sign Changes (SSC).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The SSC of the Bin
  */
	float SSC(float binned_signal[FFT_LEN],float threshold)
{
	int i;
	float ans=0;
		for(i=1;i<FFT_LEN-1;i++)
	{
		if((binned_signal[i]>binned_signal[i+1] && binned_signal[i]>binned_signal[i-1])||(binned_signal[i]<binned_signal[i+1] && binned_signal[i]<binned_signal[i-1]))
		{
			if (fabs(binned_signal[i]-binned_signal[i+1])>=threshold || fabs(binned_signal[i]-binned_signal[i-1])>=threshold) ans++;
		}
	}
	return ans;
}

	/**
  * @brief  Root Mean Square (RMS).
  * @param  binned_signal[FFT_LEN]: binned data
  * @retval The RMS of the Bin
  */
	float RMS(float binned_signal[FFT_LEN])
{
	int i;
	float ans=0;

			for(i=0;i<FFT_LEN;i++)
	{
   ans=pow(binned_signal[i],2)+ans;
	}
	ans=sqrt(ans)/FFT_LEN;
	return ans;
}





	
	
	
	
	