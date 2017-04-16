#include "main.h"

char  test=0; 

double tem =0;
double hum =0;

uint8_t BUFt[2]={0};
uint8_t BUFh[2]={0};

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{
		
   uint8_t i=10; //��������Ż��ٶ�
   while(i) 
   { 
     i--; 
   }  
}


void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}

/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
uint8_t I2C_Start(void)
{
	SDA_OUT();
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return FALSE;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	I2C_delay();
	if(SDA_read) return FALSE;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;
	I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)
{
	SDA_OUT();
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 

/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_OUT();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_OUT();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
uint8_t I2C_WaitAck(void) 	//����Ϊ:=1��ACK,=0��ACK
{
	SCL_L;
	I2C_delay();
	SDA_IN();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(uint8_t SendByte) //���ݴӸ�λ����λ//
{
    uint8_t i=8;
		SDA_OUT();
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}

/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char I2C_ReadByte(void)  //���ݴӸ�λ����λ//
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
		
		SDA_IN();
    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
			SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

//���ֽ�д��*******************************************
uint8_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //���õ���ʼ��ַ  
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

//���ֽڶ�ȡ*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
		if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck()){I2C_Stop();test=1; return FALSE;}
    I2C_SendByte((uint8_t) REG_Address);   //���õ���ʼ��ַ  
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

		REG_data= I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    //return TRUE;
	return REG_data;
}

void Cmd_Write_SHT30(uint8_t MSB,uint8_t LSB)
{
  I2C_Start();                  	//��ʼ�ź�
  I2C_SendByte(SHT30_ADDR+0);   //�����豸��ַ+д�ź�
	while(I2C_WaitAck());						//�ӻ�Ӧ��
  I2C_SendByte(MSB);    					//��������
	while(I2C_WaitAck());
	I2C_SendByte(LSB);    					//��������
	while(I2C_WaitAck());
  I2C_Stop();                   //����ֹͣ�ź�
	delay5ms();
}

void Read_SHT30(void)
{   	
		Cmd_Write_SHT30(0x20,0x32); //���ݲɼ�Ƶ��1 m/s
		//IIC_SCL=1;
		I2C_Start();   	//��ʼ�ź�
    I2C_SendByte(SHT30_ADDR+1);         //�����豸��ַ+���ź�
		while(I2C_WaitAck());
		BUFt[0]=I2C_ReadByte();  
		BUFt[1]=I2C_ReadByte();  
		//printf("tem0:%d\n",BUFt[0]);
		//printf("tem1:%d\n",BUFt[1]);
		BUFh[0]=I2C_ReadByte();  
		BUFh[1]=I2C_ReadByte();  

    I2C_Stop();                          //����ֹͣ�ź�
    delay5ms();
}

//����ת��
void Convert_SHT30(void)
{
	tem=175*(BUFt[0]*256+BUFt[1])/65535-45; //���϶�
	hum=100*(BUFh[0]*256+BUFh[1])/65535;
	BUFt[0]=0;
	BUFt[1]=0;
	BUFh[0]=0;
	BUFh[1]=0;
	printf("�¶�:%2f\n",tem);
	printf("ʪ��:%2f\n",hum);
}

void SHT30_Init(void)
{
	  
	  GPIO_InitTypeDef  GPIO_InitStructure; 
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD, ENABLE);
 
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}
