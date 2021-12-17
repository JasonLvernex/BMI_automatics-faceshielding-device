/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
unsigned long hardfault_args[8];
	static unsigned int stacked_r0;

static unsigned int stacked_r1;

static unsigned int stacked_r2;

static unsigned int stacked_r3;

static unsigned int stacked_r12;

static unsigned int stacked_lr;

static unsigned int stacked_pc;

static unsigned int stacked_psr;

static unsigned int SHCSR;

static unsigned char MFSR;

static unsigned char BFSR;

static unsigned short int UFSR;

static unsigned int HFSR;

static unsigned int DFSR;

static unsigned int MMAR;

static unsigned int BFAR;

stacked_r0 = ((unsigned long) hardfault_args[0]);

stacked_r1 = ((unsigned long) hardfault_args[1]);

stacked_r2 = ((unsigned long) hardfault_args[2]);

stacked_r3 = ((unsigned long) hardfault_args[3]);

stacked_r12 = ((unsigned long) hardfault_args[4]);

stacked_lr = ((unsigned long) hardfault_args[5]); 

stacked_pc = ((unsigned long) hardfault_args[6]);

stacked_psr = ((unsigned long) hardfault_args[7]);

SHCSR = (*((volatile unsigned long *)(0xE000ED24)));

MFSR = (*((volatile unsigned char *)(0xE000ED28)));

BFSR = (*((volatile unsigned char *)(0xE000ED29)));

UFSR = (*((volatile unsigned short int *)(0xE000ED2A)));

HFSR = (*((volatile unsigned long *)(0xE000ED2C)));  

DFSR = (*((volatile unsigned long *)(0xE000ED30)));

MMAR = (*((volatile unsigned long *)(0xE000ED34)));

BFAR = (*((volatile unsigned long *)(0xE000ED38))); 

printf("\n\n[Hard fault handler - all numbers in hex]\n\n");

printf("R0 = %x\n",stacked_r0);

printf("R1 = %x\n",stacked_r1);

printf("R2 = %x\n",stacked_r2);

printf("R3 = %x\n",stacked_r3);

printf("R12 = %x\n",stacked_r12);

printf("LR[R14] = %x subroutine call return address\n",stacked_lr);

printf("PC[R15] = %x program counter\n",stacked_pc);

printf("PSR = %x\n",stacked_psr);

printf("SHCSR = %x\n",(*((volatile unsigned long*)(0xE000ED24))));

printf("BFAR = %x\n",(*((volatile unsigned long*)(0xE000ED38))));

printf("CFSR = %x\n",(*((volatile unsigned long*)(0xE000ED28))));

printf("HFSR = %x\n",(*((volatile unsigned long*)(0xE000ED2C))));

printf("DFSR = %x\n",(*((volatile unsigned long*)(0xE000ED30))));

printf("AFSR = %x\n",(*((volatile unsigned long*)(0xE000ED3C))));

printf("SCB_SHCSR = %x\n",SCB->SHCSR);

	while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
