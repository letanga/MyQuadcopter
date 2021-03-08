#include "ALL_DEFINE.h"

volatile uint32_t SysTick_count; //系统时间计数
_st_Mpu MPU6050;   //MPU6050原始数据
_st_Mag AK8975;
_st_AngE Angle;    //当前角度姿态值
_st_Remote Remote; //遥控通道值


_st_ALL_flag ALL_flag; //系统标志位，包含解锁标志位等


PidObject pidRateX; //内环PID数据
PidObject pidRateY;
PidObject pidRateZ;

PidObject pidPitch; //外环PID数据
PidObject pidRoll;
PidObject pidYaw;

PidObject pidHeightRate;
PidObject pidHeightHigh;

void pid_param_Init(void); //PID控制参数初始化，改写PID并不会保存数据，请调试完成后直接在程序里更改 再烧录到飞控


void ALL_Init(void)
{
	cycleCounterInit();  //得到系统每个us的系统CLK个数，为以后延时函数，和得到精准的当前执行时间使用
	SysTick_Config(SystemCoreClock / 1000);	//系统滴答时钟
	IIC_Init();             //I2C初始化
	pid_param_Init();       //PID参数初始化	 
	LEDInit();              //LED闪灯初始化
	MpuInit();              //MPU6050初始化	
	USART3_Config();        //上位机串口初始化
	NRF24L01_init();				//2.4G遥控通信初始化	
	TIM2_PWM_Config();			//4路PWM初始化	
	TIM3_Config();					//系统工作周期初始化 
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










