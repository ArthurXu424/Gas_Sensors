#include "main.h"

//     Ӳ������ 
//     Pin1-TXD  -> PC11
//     Pin2-RXD  -> PC10
//     Pin3-VCC  -> VDD
//     Pin4-GND  -> GND

uint8_t USART4_RX_STA;
uint8_t USART4_RX_BUF[64];  //�������ݻ���,���64���ֽ�

unsigned char T6703_ReadGas_Cmd[]={0x15,0x04,0x13,0x8b,0x00,0x01,0x46,0x70};

/**
  * @brief  USART4��ʼ��
**/
void USART4_CO2_T6703_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART4,ENABLE);   //ʹ��USART4ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //ʹ��GPIOCʱ��

    //USART4_TX   GPIOC.10
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10

		//USART4_RX     GPIOC.11
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.11
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_0);  //���ô��ڹ���0
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_0);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 19200; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_9b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_Even;//żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART4, &USART_InitStructure); //��ʼ������4
		
		//USART4 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART4, USART_IT_RXNE, ENABLE);//��������4�����ж�
		USART_ITConfig(USART4, USART_IT_ORE, ENABLE);
		USART_Cmd(USART4, ENABLE);                    //ʹ�ܴ���4 

}

/**
  * @brief  USART4����һ���ַ���
**/
void USART4_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART4,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

