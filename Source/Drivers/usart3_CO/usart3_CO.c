#include "main.h"

//     Ӳ������ 
//     Pin10-+5V  -> 5V
//     Pin9 - RX  -> PB10
//     Pin8 - TX  -> PB11
//     Pin6 -GND  -> GND

uint8_t USART3_RX_STA;
uint8_t USART3_RX_BUF[64];  //�������ݻ���,���64���ֽ�

unsigned char ReadCO_Cmd[]={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};

/**
  * @brief  USART3��ʼ��
**/
void USART3_CO_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);   //ʹ��USART3ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //ʹ��GPIOBʱ��

    //USART3_TX   GPIOB.10
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10

		//USART3_RX   GPIOB.11
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB.11
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11 
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_4);  //���ô��ڹ���4
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_4);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 9600; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART3, &USART_InitStructure); //��ʼ������3
		
		//USART3 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������3�����ж�
		USART_ITConfig(USART3, USART_IT_ORE, ENABLE);
		USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 

}

/**
  * @brief  USART3����һ���ַ���
**/
void USART3_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART3,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

