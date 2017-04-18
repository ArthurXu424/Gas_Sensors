#include "main.h"

//     Ӳ������ 
//     G+        -> 5V
//     UART_RxD  -> PC0
//     UART_TxD  -> PC1
//     G0        -> GND

uint8_t USART6_RX_STA;
uint8_t USART6_RX_BUF[64];  //�������ݻ���,���64���ֽ�

unsigned char ReadCO2_S8_Cmd[]={0xFE,0x04,0x00,0x03,0x00,0x01,0xD5,0xC5};

/**
  * @brief  USART5��ʼ��
**/
void USART6_CO2_S8_0053_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);   //ʹ��USART6ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //ʹ��GPIOCʱ��

    //USART6_TX   GPIOC.0
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //PC.0
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.0

		//USART6_RX   GPIOC.1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PC.1
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.1 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource0,GPIO_AF_2);  //���ô��ڹ���2
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource1,GPIO_AF_2);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 9600; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART6, &USART_InitStructure); //��ʼ������6
		
		//USART6 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������6�����ж�
		USART_ITConfig(USART6, USART_IT_ORE, ENABLE);
		USART_Cmd(USART6, ENABLE);                    //ʹ�ܴ���6 

}

/**
  * @brief  USART6����һ���ַ���
**/
void USART6_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART6,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

