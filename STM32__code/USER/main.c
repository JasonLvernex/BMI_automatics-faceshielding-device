#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "UART3.h"
#include "TIM.h"
#include "scheduler.h"
#include "ALL_DATA.h"
#include "myiic.h"
#include "pca9685.h"
#include "myfeature.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
	static unsigned char ucRxBuffer[250],uccRxBuffer[250];
 unsigned char ucRxCnt = 0,uccRxCnt=0,ucccRxCnt=0;	
  static unsigned short ucccRxBuffer[250];
  u16 adcx,v,v_ref=1800,adcy;
	int f_key;
	volatile uint32_t SysTick_count; //ϵͳʱ�����
	union data adc_r;
	int actuation;
	static int base=1;
 // static int f_key;
	

void Send_data(USART_TypeDef * USARTx,u8 *s)
{
	while(*s!='\0')
	{ 
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET);	
		USART_SendData(USARTx,*s);
		s++;
	}

}

void USARTx_Send_Data(USART_TypeDef * USARTx ,u8 *buf,u8 len)   //??????,?????
{
	u8 t;
  	for(t=0;t<len;t++)		//??????
	{		   
    Send_data(USARTx,&buf[t]);
	}	 
 
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		

}

void USART_SendString(USART_TypeDef* USARTx, char *DataString)
{
	int i = 0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);										//??????????(?????????????)
	while(DataString[i] != '\0')												//??????
	{
		USART_SendData(USARTx,DataString[i]);									//????????????
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);					//????????
		USART_ClearFlag(USARTx,USART_FLAG_TC);									//??????????
		i++;
	}
}


 int main(void)
 {	 
	 	u8 key;
	u16 i=0;
	u16 j=0;


	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200	
  Initial_UART3(115200);	 
 	Adc_Init();		  		//ADC��ʼ��
	 	  KEY_Init();	
			IIC_Init();//IIC��ʼ��
	    pca_write(pca_mode1,0x0);//д��ַ
			pca_setfreq(330);//д���Ƶ�ʣ�ģ������50HZ�����ֵ��330HZ
ADC1->CR2|=1<<0;     //??AD???
ADC1->CR2|=1<<3;        //??CAL??????? 
while(ADC1->CR2&1<<3);  //?????? 
  TIM3_Config();
	   
	while(1)
	{
			
if(actuation!=0 ) //f_key!=0 //actuation!=0
{
	base=~base;
	
	switch(base)
	{
		case 1:{
				/*��ֵ���㲽�裺
				����ʱ��0.5ms-2.5ms(ռ�ձ�5%-12.5%),Ƶ��330HZ������3.03ms�����ֱ���4096
				0�㣬0.5/3.03*4096=675
				90�㣬1.5/3.03*4096=2017
				180�㣬2.5/3.03*4096=3379
				*/
				for(j=600;j<2000;j=j+5)//0·������Ȼ�����Ȼ����ת90�㣨������˲�䶯����
				{
					pca_setpwm(0,0,j);//��ת90��
					delay_ms(3);//��0�㵽180������ʱ�������������ڿ���Ч��
				}
				break;
			
		        }
			
		default:
		{
							/*��ֵ���㲽�裺
				����ʱ��0.5ms-2.5ms(ռ�ձ�5%-12.5%),Ƶ��330HZ������3.03ms�����ֱ���4096
				0�㣬0.5/3.03*4096=675
				90�㣬1.5/3.03*4096=2017
				180�㣬2.5/3.03*4096=3379
				*/
				for(j=2000;j>600;j=j-5)//0·������Ȼ�����Ȼ����ת90�㣨������˲�䶯����
				{
					pca_setpwm(0,0,j);//��ת90��
					delay_ms(3);//��0�㵽180������ʱ�������������ڿ���Ч��
				}
				break;
		}
	}
	

					//delay_ms(300);//0·���ת��180����ӳ�һ��ʱ�䣬1·�����ʼת
			}

	}
 }

 void CopeSerial3Data(unsigned short ucData)
{	
	ucccRxBuffer[ucccRxCnt++]=ucData;	//���յ������ݴ��뻺������
	ucccRxCnt=0;
}
