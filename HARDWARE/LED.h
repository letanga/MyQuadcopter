#ifndef __LED_H
#define __LED_H

#include "delay.h"

//机身后灯			 
#define fLED_H() GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define fLED_L() GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define fLED_Toggle() GPIO_WriteBit(GPIOB,GPIO_Pin_1,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1))); 

#define hLED_H() GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define hLED_L() GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define hLED_Toggle() GPIO_WriteBit(GPIOB,GPIO_Pin_2,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_2)));

//-------------------------------------------------
//机身前灯			 
#define aLED_H() GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define aLED_L() GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define aLED_Toggle() GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));

#define bLED_H() GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define bLED_L() GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define bLED_Toggle() GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9)));

typedef struct
{
	uint16_t FlashTime;
	enum
	{
		AlwaysOn, 
		AlwaysOff, 
		AllFlashLight,
		AlternateFlash, 
		WARNING,
		DANGEROURS,
		GET_OFFSET	
	}status; 
}sLED;	

extern sLED LED;
extern void LEDInit(void);
extern void LEDtest(void);
extern void LEDRefresh(void);

#endif 


