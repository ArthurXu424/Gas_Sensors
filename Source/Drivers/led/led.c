#include "main.h"

//     Ӳ������ 
//     LD2  -> PA5

//LED IO��ʼ��
void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.5
	 GPIO_SetBits(GPIOA,GPIO_Pin_5);						 //PA5 �����

}
