#include "main.h"

//     Ӳ������ 
//     Pin1-VCC  -> 5V
//     Pin2-GND  -> GND
//     Pin4-RXD  -> PA9
//     Pin5-TXD  -> PA10

uint8_t USART_RX_STA;
uint8_t USART_RX_BUF[64];  //�������ݻ���,���64���ֽ�

/**
  * @brief  USART1��ʼ��
**/
void USART1_PM25_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);   //ʹ��USART1ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     //ʹ��GPIOAʱ��

    //USART1_TX   GPIOA.9
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

		//USART1_RX     GPIOA.10
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA.10
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10 
	
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);  //���ô��ڹ���1
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 9600; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART1, &USART_InitStructure); //��ʼ������1
		
		//USART1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������1�����ж�
		USART_ITConfig(USART1, USART_IT_ORE, ENABLE);
		USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

