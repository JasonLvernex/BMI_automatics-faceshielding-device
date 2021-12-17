#ifndef _I2C_H_
  #define _I2C_H_

  #include "stm32f10x.h"
  #include "system_stm32f10x.h"

#define CLI()      __set_PRIMASK(1)  
#define SEI()      __set_PRIMASK(0)

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


#define TRUE  0
#define FALSE -1

  #define IIC_RCC       RCC_APB2Periph_GPIOB
  #define IIC_GPIO      GPIOB
  #define SCL_PIN       GPIO_Pin_6
  #define SDA_PIN       GPIO_Pin_7

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6 /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 /* GPIO_ResetBits(GPIOB , GPIO_Pin_10) */

#define SDA_H         GPIOB->BSRR = GPIO_Pin_7 /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7 /* GPIO_ResetBits(GPIOB , GPIO_Pin_11) */

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) */
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */


//0��ʾд
#define	I2C_Direction_Trans   0
//����ʾ��
#define	I2C_Direction_Rec      1	 
/*====================================================================================================*/
/*====================================================================================================*/
//PB6 SCL
//PB7 SDA
//return 0:success   1:failed
extern void IIC_Init(void);
//----------------------------------------------------------------------
extern int8_t IIC_Write_One_Byte(uint8_t addr,uint8_t reg,uint8_t data);
extern int8_t IIC_Read_One_Byte(uint8_t addr,uint8_t reg);	 
extern int8_t IIC_Write_Bytes(uint8_t addr,uint8_t reg,uint8_t *data,uint8_t len);
extern int8_t IIC_read_Bytes(uint8_t addr,uint8_t reg,uint8_t *data,uint8_t len);
//----------------------------------------------------------------------f


/*====================================================================================================*/
/*====================================================================================================*/

#endif
