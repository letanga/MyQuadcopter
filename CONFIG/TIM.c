#include "stm32f10x.h"
#include "delay.h"
#include "TIM.h"
#include "ALL_DEFINE.h"

void TIM2_PWM_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ʹ��GPIOAʱ��ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
    GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* ʹ�ܶ�ʱ��2ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 999; //��ʱ���������� 0-999  1000	
  TIM_TimeBaseStructure.TIM_Prescaler = 8; //����Ԥ��Ƶ��8+1��Ƶ   8K PWMƵ��
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
    //��������ֵ�������������������ֵʱ����ƽ��������(��ռ�ձ�) ��ʼֵ0
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    //����ʱ������ֵС�ڶ�ʱ�趨ֵʱΪ�ߵ�ƽ
  /* ʹ��ͨ��1 */
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  /* ʹ��ͨ��2 */
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
  /* ʹ��ͨ��3 */
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  /* ʹ��ͨ��4 */
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM2, ENABLE); // ʹ��TIM2���ؼĴ���ARR
  TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��2
}



//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	TIM_TimeBaseStructure.TIM_Period = 299; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������300Ϊ3ms
	TIM_TimeBaseStructure.TIM_Prescaler =719; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  100Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����						 
}


void TIM3_IRQHandler(void)   //TIM3�ж� 3ms
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		static uint8_t cnt_3ms = 0;
		static uint8_t cnt_6ms = 0;	 
		SysTick_count++;
		cnt_3ms++;
		cnt_6ms++;		
		if(cnt_3ms == 1)  //1ms����һ��
		{
			cnt_3ms = 0;
			MpuGetData();
			RC_Analy();			
			FlightPidControl(0.003f);
			MotorControl();
		}		
		if(cnt_6ms == 2) //6ms����һ��
		{
			cnt_6ms = 0;
			GetAngle(&MPU6050,&Angle,0.00626f);
		}		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	}
}
