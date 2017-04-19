/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//USART1��������
extern	uint8_t USART_RX_STA;
extern	uint8_t USART_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

//USART3��������
extern	uint8_t USART3_RX_STA;
extern	uint8_t USART3_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

//USART4��������
extern	uint8_t USART4_RX_STA;
extern	uint8_t USART4_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

//USART5��������
extern	uint8_t USART5_RX_STA;
extern	uint8_t USART5_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

//USART6��������
extern	uint8_t USART6_RX_STA;
extern	uint8_t USART6_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

//USART7��������
extern	uint8_t USART7_RX_STA;
extern	uint8_t USART7_RX_BUF[64];  //�������ݻ�����,���64���ֽ�

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)     //����1�жϷ�����
{
		uint8_t Res;
    static char start=0;
		
		if (USART_GetITStatus(USART1, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART1,USART_IT_ORE);      
        USART_ReceiveData( USART1 );  
  
    }

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);  
				Res =USART_ReceiveData(USART1); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(Res == 0x42) //������յ��ĵ�һλ������0X42(����ǲ鿴�������ֲ��֪��)
				{
						USART_RX_STA = 0;     //����������ֵ��0��ʼ
						start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X4D(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(start == 1)
				{
					USART_RX_BUF[USART_RX_STA] = Res ; //�ѽ��յ������ݴ浽��������
					USART_RX_STA++;
					if(USART_RX_STA >= 23 && (USART_RX_BUF[1]==0x4d))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("PM2.5:%d\n",USART_RX_BUF[6]*256+USART_RX_BUF[7]);
							printf("PM10:%d\n",USART_RX_BUF[14]*256+USART_RX_BUF[15]);
							start  = 0;
							USART_RX_STA=0;//���¿�ʼ����   
							USART_RX_BUF[0] = 0;
					}
				}                   
    }
}

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_8_IRQHandler(void)
{
		uint8_t USART3_Res;
    static char USART3_start=0;
	
		uint8_t USART4_Res;
    static char USART4_start=0;
	
		uint8_t USART5_Res;
    static char USART5_start=0;
	
		uint8_t USART6_Res;
    static char USART6_start=0;
	
		uint8_t USART7_Res;
    static char USART7_start=0;
		
	
	  //USART3�����жϴ���
		if (USART_GetITStatus(USART3, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART3,USART_IT_ORE);      
        USART_ReceiveData( USART3 );  
  
    }

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART3,USART_IT_RXNE);  
				USART3_Res =USART_ReceiveData(USART3); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(USART3_Res == 0x01) //������յ��ĵ�һλ������0X42(����ǲ鿴�������ֲ��֪��)
				{
						USART3_RX_STA = 0;     //����������ֵ��0��ʼ
						USART3_start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X4D(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(USART3_start == 1)
				{
					USART3_RX_BUF[USART3_RX_STA] = USART3_Res ; //�ѽ��յ������ݴ浽��������
					USART3_RX_STA++;
					if(USART3_RX_STA >= 7 && (USART3_RX_BUF[1]==0x03))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CO:%d\n",USART3_RX_BUF[3]*256+USART3_RX_BUF[4]);
							USART3_start  = 0;
							USART3_RX_STA=0;//���¿�ʼ����   
							USART3_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART4�����жϴ���
		if (USART_GetITStatus(USART4, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART4,USART_IT_ORE);      
        USART_ReceiveData( USART4 );  
  
    }

    if(USART_GetITStatus(USART4, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART4,USART_IT_RXNE);  
				USART4_Res =USART_ReceiveData(USART4); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(USART4_Res == 0x15) //������յ��ĵ�һλ������0X15(����ǲ鿴�������ֲ��֪��)
				{
						USART4_RX_STA = 0;     //����������ֵ��0��ʼ
						USART4_start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X04(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(USART4_start == 1)
				{
					USART4_RX_BUF[USART4_RX_STA] = USART4_Res ; //�ѽ��յ������ݴ浽��������
					USART4_RX_STA++;
					if(USART4_RX_STA >= 6 && (USART4_RX_BUF[1]==0x04))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CO2:%d\n",USART4_RX_BUF[3]*256+USART4_RX_BUF[4]);
							USART4_start  = 0;
							USART4_RX_STA=0;//���¿�ʼ����   
							USART4_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART5�����жϴ���
		if (USART_GetITStatus(USART5, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART5,USART_IT_ORE);      
        USART_ReceiveData( USART5 );  
  
    }

    if(USART_GetITStatus(USART5, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART5,USART_IT_RXNE);  
				USART5_Res =USART_ReceiveData(USART5); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(USART5_Res == 0x01) //������յ��ĵ�һλ������0X01(����ǲ鿴�������ֲ��֪��)
				{
						USART5_RX_STA = 0;     //����������ֵ��0��ʼ
						USART5_start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X03(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(USART5_start == 1)
				{
					USART5_RX_BUF[USART5_RX_STA] = USART5_Res ; //�ѽ��յ������ݴ浽��������
					USART5_RX_STA++;
					if(USART5_RX_STA >= 7 && (USART5_RX_BUF[1]==0x03))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CH2O:%d\n",USART5_RX_BUF[3]*256+USART5_RX_BUF[4]);
							USART5_start  = 0;
							USART5_RX_STA=0;//���¿�ʼ����   
							USART5_RX_BUF[0] = 0;
					}
				}                   
    }
		
	  //USART6�����жϴ���
		if (USART_GetITStatus(USART6, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART6,USART_IT_ORE);      
        USART_ReceiveData( USART6 );  
  
    }

    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART6,USART_IT_RXNE);  
				USART6_Res =USART_ReceiveData(USART6); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(USART6_Res == 0xFE) //������յ��ĵ�һλ������0XFE(����ǲ鿴�������ֲ��֪��)
				{
						USART6_RX_STA = 0;     //����������ֵ��0��ʼ
						USART6_start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X04(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(USART6_start == 1)
				{
					USART6_RX_BUF[USART6_RX_STA] = USART6_Res ; //�ѽ��յ������ݴ浽��������
					USART6_RX_STA++;
					if(USART6_RX_STA >= 7 && (USART6_RX_BUF[1]==0x04))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CO2 From S8:%d\n",USART6_RX_BUF[3]*256+USART6_RX_BUF[4]);
							USART6_start  = 0;
							USART6_RX_STA=0;//���¿�ʼ����   
							USART6_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART7�����жϴ���
		if (USART_GetITStatus(USART7, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART7,USART_IT_ORE);      
        USART_ReceiveData( USART7 );  
  
    }

    if(USART_GetITStatus(USART7, USART_IT_RXNE) != RESET)  //�����ж�
		{
				USART_ClearITPendingBit(USART7,USART_IT_RXNE);  
				USART7_Res =USART_ReceiveData(USART7); //��ȡ���յ�������
				//USART_SendData(USART1,Res);
				if(USART7_Res == 0xFF) //������յ��ĵ�һλ������0XFF(����ǲ鿴�������ֲ��֪��)
				{
						USART7_RX_STA = 0;     //����������ֵ��0��ʼ
						USART7_start = 1;  //�����������ȷ���ڶ�λ�Ƿ���յ���0X17(���Ҳ�ǲ鿴�������ֲ��֪��)
				}

				if(USART7_start == 1)
				{
					USART7_RX_BUF[USART7_RX_STA] = USART7_Res ; //�ѽ��յ������ݴ浽��������
					USART7_RX_STA++;
					if(USART7_RX_STA >= 9 && (USART7_RX_BUF[1]==0x17))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CH2O From Dart 2-FE5:%d\n",USART7_RX_BUF[4]*256+USART7_RX_BUF[5]);
							USART7_start  = 0;
							USART7_RX_STA=0;//���¿�ʼ����   
							USART7_RX_BUF[0] = 0;
					}
				}                   
    }
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
