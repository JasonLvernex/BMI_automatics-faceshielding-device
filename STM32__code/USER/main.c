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
 ALIENTEK 战舰STM32F103开发板实验17
 ADC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
	static unsigned char ucRxBuffer[250],uccRxBuffer[250];
 unsigned char ucRxCnt = 0,uccRxCnt=0,ucccRxCnt=0;	
  static unsigned short ucccRxBuffer[250];
  u16 adcx,v,v_ref=1800,adcy;
	int f_key;
	volatile uint32_t SysTick_count; //系统时间计数
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200	
  Initial_UART3(115200);	 
 	Adc_Init();		  		//ADC初始化
	 	  KEY_Init();	
			IIC_Init();//IIC初始化
	    pca_write(pca_mode1,0x0);//写地址
			pca_setfreq(330);//写舵机频率，模拟电机给50HZ，数字电机330HZ
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
				/*数值计算步骤：
				脉冲时间0.5ms-2.5ms(占空比5%-12.5%),频率330HZ（周期3.03ms），分辨率4096
				0°，0.5/3.03*4096=675
				90°，1.5/3.03*4096=2017
				180°，2.5/3.03*4096=3379
				*/
				for(j=600;j<2000;j=j+5)//0路舵机，先回正，然后旋转90°（回正是瞬间动作）
				{
					pca_setpwm(0,0,j);//旋转90°
					delay_ms(3);//从0°到180°增长时缓慢增长，易于看到效果
				}
				break;
			
		        }
			
		default:
		{
							/*数值计算步骤：
				脉冲时间0.5ms-2.5ms(占空比5%-12.5%),频率330HZ（周期3.03ms），分辨率4096
				0°，0.5/3.03*4096=675
				90°，1.5/3.03*4096=2017
				180°，2.5/3.03*4096=3379
				*/
				for(j=2000;j>600;j=j-5)//0路舵机，先回正，然后旋转90°（回正是瞬间动作）
				{
					pca_setpwm(0,0,j);//旋转90°
					delay_ms(3);//从0°到180°增长时缓慢增长，易于看到效果
				}
				break;
		}
	}
	

					//delay_ms(300);//0路舵机转到180°后延迟一段时间，1路舵机开始转
			}

	}
 }

 void CopeSerial3Data(unsigned short ucData)
{	
	ucccRxBuffer[ucccRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	ucccRxCnt=0;
}
