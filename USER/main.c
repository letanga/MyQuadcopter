#include "ALL_DEFINE.h"
#include "init.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //2��bit����ռ���ȼ���2��bit�������ȼ�
	ALL_Init();//ϵͳ��ʼ��
	while(1)
	{
		ANTO_polling(); 	//������λ��
		LEDRefresh(); 			//LEDˢ��
	}
}

