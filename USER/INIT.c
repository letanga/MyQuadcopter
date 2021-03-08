#include "ALL_DEFINE.h"

volatile uint32_t SysTick_count; //ϵͳʱ�����
_st_Mpu MPU6050;   //MPU6050ԭʼ����
_st_Mag AK8975;
_st_AngE Angle;    //��ǰ�Ƕ���ֵ̬
_st_Remote Remote; //ң��ͨ��ֵ


_st_ALL_flag ALL_flag; //ϵͳ��־λ������������־λ��


PidObject pidRateX; //�ڻ�PID����
PidObject pidRateY;
PidObject pidRateZ;

PidObject pidPitch; //�⻷PID����
PidObject pidRoll;
PidObject pidYaw;

PidObject pidHeightRate;
PidObject pidHeightHigh;

void pid_param_Init(void); //PID���Ʋ�����ʼ������дPID�����ᱣ�����ݣ��������ɺ�ֱ���ڳ�������� ����¼���ɿ�


void ALL_Init(void)
{
	cycleCounterInit();  //�õ�ϵͳÿ��us��ϵͳCLK������Ϊ�Ժ���ʱ�������͵õ���׼�ĵ�ǰִ��ʱ��ʹ��
	SysTick_Config(SystemCoreClock / 1000);	//ϵͳ�δ�ʱ��
	IIC_Init();             //I2C��ʼ��
	pid_param_Init();       //PID������ʼ��	 
	LEDInit();              //LED���Ƴ�ʼ��
	MpuInit();              //MPU6050��ʼ��	
	USART3_Config();        //��λ�����ڳ�ʼ��
	NRF24L01_init();				//2.4Gң��ͨ�ų�ʼ��	
	TIM2_PWM_Config();			//4·PWM��ʼ��	
	TIM3_Config();					//ϵͳ�������ڳ�ʼ�� 
}

void pid_param_Init(void)
{
	pidRateX.kp = 2.0f;
	pidRateY.kp = 2.0f;
	pidRateZ.kp = 4.0f;
	
	pidRateX.ki = 0.0f;
	pidRateY.ki = 0.0f;
	pidRateZ.ki = 0.0f;	
	
	pidRateX.kd = 0.08f;
	pidRateY.kd = 0.08f;
	pidRateZ.kd = 0.5f;	
	
	pidPitch.kp = 7.0f;
	pidRoll.kp = 7.0f;
	pidYaw.kp = 7.0f;	
}










