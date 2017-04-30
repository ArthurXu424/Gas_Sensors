#include "main.h"

//     Ӳ������ 
//     VCC  -> 3.3V
//     TXD  -> PC2
//     RXD  -> PC3
//     GND  -> GND

uint8_t USART8_RX_STA;
uint8_t USART8_RX_BUF[64];  //�������ݻ���,���64���ֽ�

unsigned char USART8_Send_Cmd_01[]={0x53,0x32,0x01,0x39,0x00,0x00,0x00};
unsigned char USART8_Send_Cmd_0C[]={0x53,0x32,0x0C,0x00,0x00,0x00,0x00};
unsigned char USART8_Send_Gas_Data[]={0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char USART8_Send_Cmd_0C_Data = 0;
uint32_t USART8_Send_Cmd_04_Data[10];
uint8_t USART8_Cmd_04_Data[64];

/**
  * @brief  USART8��ʼ��
**/
void USART8_Comm_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART8,ENABLE);   //ʹ��USART8ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //ʹ��GPIOCʱ��

    //USART8_TX   GPIOC.2
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PC.2
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.2

		//USART8_RX   GPIOC.3
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC.3
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.3 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource2,GPIO_AF_2);  //���ô��ڹ���2
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_2);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 9600; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART8, &USART_InitStructure); //��ʼ������8
		
		//USART8 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART8, USART_IT_RXNE, ENABLE);//��������8�����ж�
		USART_ITConfig(USART8, USART_IT_ORE, ENABLE);
		USART_Cmd(USART8, ENABLE);                    //ʹ�ܴ���8 

}

/**
  * @brief  USART8����һ���ַ���
**/
void USART8_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART8,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

