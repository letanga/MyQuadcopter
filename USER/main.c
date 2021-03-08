#include "ALL_DEFINE.h"
#include "init.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //2个bit的抢占优先级，2个bit的子优先级
	ALL_Init();//系统初始化
	while(1)
	{
		ANTO_polling(); 	//匿名上位机
		LEDRefresh(); 			//LED刷新
	}
}

