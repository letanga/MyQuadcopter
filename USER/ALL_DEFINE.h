#ifndef __ALL_DEFINE_H__
#define __ALL_DEFINE_H__
#include "stm32f10x.h"
#include "ALL_DATA.h"
#include "INIT.h"
#include "I2C.h"
#include "SPI.h"
#include "nrf24l01.h"
#include "USART.h"
#include  "TIM.h"
#include "LED.h"
#include "mpu6050.h"
#include "imu.h"
#include "ANO_DT.h"
#include "Remote.h"
#include "control.h"
#include "myMath.h"
#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1
#define ZY_31_SLAVE_ADDRESS 0xC0
#define MODULE_REST 0x20
#define MPU6050_GET_OFFSET 0x21
#define MS5611_GET_OFFSET 0x22
#define MPU_READ 0X30
#define ANGLE_READ 0X32

#define HEIGHT_READ 0X33
#define RATE_READ 0X34

#endif

