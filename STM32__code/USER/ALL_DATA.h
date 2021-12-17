#ifndef _ALL_USER_DATA_H_
#define _ALL_USER_DATA_H_

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       long long int64_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       long long uint64_t;


#define NULL 0
extern volatile uint32_t SysTick_count;


typedef struct{
	int16_t accX;
	int16_t accY;
	int16_t accZ;
	int16_t gyroX;
	int16_t gyroY;
	int16_t gyroZ;
}_st_Mpu;


typedef volatile struct
{
	uint8_t unlock;
	uint8_t unfold_rd;//展开完成标志位
	uint8_t flight_mode;//flightmode 1:auto 0:manual
	uint8_t maintain_hight;//接收控制前的保持高度
  uint8_t manual_flag;
	uint8_t procesure_rd;
}_st_ALL_flag;


union data{
    uint8_t sending_seg[2];
    uint16_t read_adc;
};





#endif

