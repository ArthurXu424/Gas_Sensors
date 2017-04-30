#include "main.h"

void TIM2_Init(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   
  
    TIM_DeInit(TIM2);  
  
    TIM_TimeBaseStructure.TIM_Period=2000-1;  //�Զ���װ�ؼĴ�����ֵ 
    TIM_TimeBaseStructure.TIM_Prescaler=(24000-1);         //ʱ��Ԥ��Ƶ��  
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //������Ƶ  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);  
	
		//TIM2 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC

    TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //�������жϱ�־
  
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);       //����TIM2�ж�
  
    TIM_Cmd(TIM2,ENABLE);                              //ʹ��TIM2 
}

