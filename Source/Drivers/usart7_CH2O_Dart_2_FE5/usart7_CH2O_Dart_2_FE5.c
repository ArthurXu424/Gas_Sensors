#include "main.h"

//     Ӳ������ 
//     Pin1-VCC  -> 5V
//     Pin2-TXD  -> PC7
//     Pin3-RXD  -> PC6
//     Pin4-GND  -> GND

uint8_t USART7_RX_STA;
uint8_t USART7_RX_BUF[64];  //�������ݻ���,���64���ֽ�

/**
  * @brief  USART7��ʼ��
**/
void USART7_CH2O_Dart_2_FE5_Init(void)
{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART7,ENABLE);   //ʹ��USART7ʱ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //ʹ��GPIOCʱ��

    //USART7_TX   GPIOC.6
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PC.6
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.6

		//USART7_RX   GPIOC.7
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PC.7
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�����������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.7 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_1);  //���ô��ڹ���1
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_1);
		
		//USART��ʼ������

    USART_InitStructure.USART_BaudRate = 9600; //���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
		USART_Init(USART7, &USART_InitStructure); //��ʼ������7
		
		//USART7 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=2 ;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ��������ʼ��NVIC
                    
		USART_ITConfig(USART7, USART_IT_RXNE, ENABLE);//��������7�����ж�
		USART_ITConfig(USART7, USART_IT_ORE, ENABLE);
		USART_Cmd(USART7, ENABLE);                    //ʹ�ܴ���7 

}

/**
  * @brief  USART7����һ���ַ���
**/
void USART7_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART7,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

