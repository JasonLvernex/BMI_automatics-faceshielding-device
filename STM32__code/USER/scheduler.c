//========================================================================
//	爱好者电子工作室-淘宝 https://devotee.taobao.com/
//	STM32四轴爱好者QQ群: 810149456
//	作者：小刘
//	电话:13728698082
//	邮箱:1042763631@qq.com
//	日期：2018.05.17
//	版本：V1.0
//========================================================================
//套件购买地址：https://devotee.taobao.com/
//                 爱好者电子工作室
//特此声明：
//
//         此程序只能用作学习，如用商业用途。必追究责任！
//          
//
//
//#include "ALL_DEFINE.h"
#include "ALL_DATA.h"
#include "scheduler.h"
#include "TIM.h"
#include "stm32f10x.h"
#include "sys.h"
#include "adc.h"
#include "UART3.h"
#include "usart.h"
#include "key.h"
#include "delay.h"
#include "myfeature.h"
#include "adc.h"
#include "network_evaluate.h"

extern u16 adcx,adcy;
extern union data adc_r;
static u16 adc_ave=0,data_2send=0,v=0,adc_ave1=0,data_2send1=0,v2=0;
//static float test_v1[64]={158.70,162.30,161.90,155.90,153.80,150.80,151.90,158.60,162.40,161.20,158.70,158.70,158.70,158.70,158.70,158.70};
//static float test_v2[64]={170.60,173.70,173.90,168.00,170.60,176.60,172.30,171.50,173.40,171.90,170.60,170.60,170.60,170.60,170.60,170.60};
//static float test_v3[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//static float test_flag[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static float v1_buff[64],v2_buff[64],flag_buff[64];
static int countter=0,kk=0;
static float features[32];
static float ffts[2],*fft1,*fft2,input_fft1[64],input_fft2[64];
extern int actuation;
static float action_test[2];
extern int f_key;
int uart_float[32];
static int fag=0;


union float_data
{
    float f_data;
    uint8_t byte[4];
}ffg[32];

//extern int f_key;

void TIM3_IRQHandler(void)   //TIM3中断 1ms
{
		int i=0;
	   int j=0;
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{  
		
		static uint8_t cnt_1ms = 0;
		static uint8_t cnt_5ms = 0;	 
		static uint8_t cnt_10ms = 0;
		SysTick_count++;
		cnt_1ms++;
		cnt_5ms++;
		cnt_10ms++;
		//GPIOB->ODR ^= GPIO_Pin_1;// test sentence
		
		
		if(cnt_1ms == 1)  //3ms更新一次
		{
			cnt_1ms = 0;
		//adcx=Get_Adc_Average(ADC_Channel_1,10);
		adcx=Get_Adc(ADC_Channel_1);
		adcy=Get_Adc(ADC_Channel_2);
		adcx=(3.3/4096)*1000*adcx;//adcx-v_ref
		adcy=(3.3/4096)*1000*adcy;
		adc_ave=adc_ave+adcx;
		adc_ave1=adc_ave1+adcy;
		adc_r.read_adc=adcx;

			
		//printf("your data is:%double",adcx );
///		USARTx_Send_Data(USART3,adc_r.sending_seg,2);

		}		
		if(cnt_5ms == 1) //10ms更新一次
		{
			cnt_5ms = 0;
			v1_buff[cnt_10ms]=((double)adcx)/1000;
			v2_buff[cnt_10ms]=((double)adcy)/1000;
			
			f_key=(int)KEY_Scan();
			flag_buff[cnt_10ms]=f_key;
			countter++;
			//if (countter>=10) countter=0;
			
			data_2send=adc_ave/5;
			data_2send1=adc_ave1/5;
			adc_ave=0;
			adc_ave1=0;
		v=(int)adcx; 
		v2=(int)adcy;
		//f_key=(int)f_key;

//** is the part of the original
		
			//v1
  /* USART_SendData(USART3,0x76);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x31);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x3D);
   while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); */
//**		if ((v/1000)>0){
//**	           USART_SendData(USART3,(48+v/1000));
	          /*while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	           USART_SendData(USART3,0x2E);*/
//**	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);}
//**	   if ((v%1000/100)>0){
//**						USART_SendData(USART3,(48+v%1000/100));
//**	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);}
	 
//**	 USART_SendData(USART3,(48+v%1000%100/10));
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,0x2E);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,(48+v%1000%100%10/1));
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,(48+v%1000%100%10%1));		
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	/* USART_SendData(USART3,0x6D);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x76);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);*/
//**	USART_SendData(USART3,0x20);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 
//**	 USART_SendData(USART3,0x20);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 
						
	//v2					
	/* USART_SendData(USART3,0x76);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x32);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x3D);
   while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);*/
//**		if ((v2/1000)>0){
//**	           USART_SendData(USART3,(48+v2/1000));
	          /*while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	           USART_SendData(USART3,0x2E);*/
//**	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);}
//**	   if ((v2%1000/100)>0){
//**						USART_SendData(USART3,(48+v2%1000/100));
//**	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);}
	 
//**	 USART_SendData(USART3,(48+v2%1000%100/10));
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,0x2E);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,(48+v2%1000%100%10/1));
//**   while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
//**	 USART_SendData(USART3,(48+v2%1000%100%10%1));		
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	/* USART_SendData(USART3,0x6D);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x76);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);*/
//**	 USART_SendData(USART3,0x20);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 
//**	 USART_SendData(USART3,0x20);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);


//flag
	/* USART_SendData(USART3,0x46);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x3D);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);*/
//**	 USART_SendData(USART3,48+f_key);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);	 
//**	 USART_SendData(USART3,0x0A);
//**	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 						
		}

		
		
if(cnt_10ms == 64)
{
cnt_10ms=0;
	//static double flag_label_t,fft_trans_v1,fft_trans_v2,FMN_v1,FMDv1,MFMD_v1,MFMN_v1,MMAV1_v1,MMAV2_v1,MAV_v1,SSI_v1,WAMP_v1,WL_v1,ZC_v1,IEMG_v1,VAR_v1,SSC_v1,RMS_v1;
	
	ADC_Cmd(ADC1, DISABLE);
	fag= flag_label(flag_buff);
	
/*	for(j=0;j<64;j++)
	{
		input_fft1[j]=test_v1[j];
		input_fft2[j]=test_v2[j];
	}*/
//	if(kk==0)
//	{
	 fft1=fft_trans(v1_buff);	
	 fft2=fft_trans(v1_buff);
//	 kk++;
//	}
	for(j=0;j<64;j++)
	{
		input_fft1[j]=*(fft1+j);
		input_fft2[j]=*(fft2+j);
	}
	
	features[0]= FFMN(input_fft1);
	features[1]= FFMD(input_fft1);
	features[2]= MFMD(input_fft1);
  features[3]= MFMN(input_fft1);
	features[4]= MMAV1(v1_buff);
	features[5]= MMAV2(v1_buff);
	features[6]= MAV(v1_buff);
	features[7]= SSI(v1_buff);
	features[8]= WAMP(v1_buff, 150);
	features[9]= WL(v1_buff);
	features[10]= ZC(v1_buff,150, 10);
	features[11]= IEMG(v1_buff);
	features[12]= VAR(v1_buff);
	features[13]= SSC(v1_buff,150);
	features[14]= RMS(v1_buff);
	features[15] =FR(input_fft1);
		
	features[16]= FFMN(input_fft2);
	features[17]= FFMD(input_fft2);
	features[18]= MFMD(input_fft2);
  features[19]= MFMN(input_fft2);
	features[20]= MMAV1(v2_buff);
	features[21]= MMAV2(v2_buff);
	features[22]= MAV(v2_buff);
	features[23]= SSI(v2_buff);
	features[24]= WAMP(v2_buff, 150);
	features[25]= WL(v2_buff);
	features[26]= ZC(v2_buff,150, 10);
	features[27]= IEMG(v2_buff);
	features[28]= VAR(v2_buff);
	features[29]= SSC(v2_buff,150);
	features[30]= RMS(v2_buff);
	features[31] =FR(input_fft2);
	
	ADC_Cmd(ADC1, ENABLE);
	
	action_test[1]=networkEvaluate(features);
	if (action_test[1]>0.07) {actuation=1;}
	else actuation=0;
	

	//print NN data
/*	for(i=0;i<32;i++)
	{ int zero_flag=0;
		uart_float[i]=(int)(features[i]*1000);
		
		if ((uart_float[i]/10000000000)>0){
	           USART_SendData(USART3,(48+uart_float[i]/10000000000));
             while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
		         zero_flag++;}
   if ((uart_float[i]%10000000000/1000000000)>0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000/1000000000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	          zero_flag++;}
	 if(zero_flag!=0&&(uart_float[i]%10000000000/1000000000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
   if ((uart_float[i]%10000000000%1000000000/100000000)>0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000/100000000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	          zero_flag++;}
	 	 if(zero_flag!=0&&(uart_float[i]%10000000000%1000000000/100000000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
   if ((uart_float[i]%10000000000%1000000000%100000000/10000000)>0&&zero_flag==0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000/10000000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	          zero_flag++;}
	 	 	 if(zero_flag!=0&&(uart_float[i]%10000000000%1000000000%100000000/10000000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
   if ((uart_float[i]%10000000000%1000000000%100000000%10000000/1000000)>0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000%10000000/1000000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	          zero_flag++;}
	  if(zero_flag!=0&&(uart_float[i]%10000000000%1000000000%100000000%10000000/1000000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
   if ((uart_float[i]%10000000000%1000000000%100000000%10000000%1000000/100000)>0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000%10000000%1000000/100000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	         zero_flag++; }
	 	  if(zero_flag!=0&&(uart_float[i]%10000000000%1000000000%100000000%10000000%1000000/100000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
	 if ((uart_float[i]%10000000000%1000000000%100000000%10000000%1000000%100000/10000)>0){
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000%10000000%1000000%100000/10000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	          zero_flag++;}
	 	 	  if(zero_flag!=0&&(uart_float[i]%10000000000%1000000000%100000000%10000000%1000000%100000/10000)==0){
		        USART_SendData(USART3,(48+0));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 };
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000%10000000%1000000%100000%10000/1000));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
  	USART_SendData(USART3,0x2E);
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);	
						USART_SendData(USART3,(48+uart_float[i]%10000000000%1000000000%100000000%10000000%1000000%100000%10000%1000/100));
	          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
 

	 
	 USART_SendData(USART3,(48+uart_float[i]%10000000%1000000%100000%10000%1000%100/10));
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);

	 USART_SendData(USART3,(48+uart_float[i]%1000%100%10/1));
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,(48+uart_float[i]%1000%100%10%1));		
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	 USART_SendData(USART3,0x20);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 
	 USART_SendData(USART3,0x20);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	}*/
	/* USART_SendData(USART3,48+fag);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);	 
	 USART_SendData(USART3,0x0A);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 
	
	 USART_SendData(USART3,0x0A);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET); 	*/
}	

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  //清除TIMx的中断待处理位:TIM 中断源 
	}
} 


