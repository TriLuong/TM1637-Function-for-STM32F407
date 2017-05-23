#include "TM1637_Function.h"

const unsigned char digitToSegment[] = {
 // XGFEDCBA
  0x3F,    // 0 
  0x06,    // 1
  0x5B,    // 2
  0x4F,    // 3
  0x66,    // 4
  0x6D,    // 5
  0x7D,    // 6
  0x07,    // 7
  0x7F,    // 8
  0x6F,    // 9
  0x00,    // tat LED
};

void TM1637_Start()
{
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,1);
	HAL_GPIO_WritePin(GPIOE,DIO_Pin,1);
	HAL_GPIO_WritePin(GPIOE,DIO_Pin,0);
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,0);	
}

void TM1637_Stop()
{
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,0);
	HAL_GPIO_WritePin(GPIOE,DIO_Pin,0);
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,1);
	HAL_GPIO_WritePin(GPIOE,DIO_Pin,1);	
}

void TM1637_Write(unsigned char Data)
{
	for(int i=0; i<8;i++)
	{
		HAL_GPIO_WritePin(GPIOE,CLK_Pin,0);
		HAL_GPIO_WritePin(GPIOE,DIO_Pin,Data&0x01); // Read LSB first
		Data=Data>>1;
		HAL_GPIO_WritePin(GPIOE,CLK_Pin,1);
		HAL_GPIO_WritePin(GPIOE,CLK_Pin,0);
	}
	
	//Generate ACK
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,1);
	HAL_GPIO_WritePin(GPIOE,CLK_Pin,0);
	
}	

void TM1637_disPlay(unsigned char value, unsigned led_pos, unsigned char led_status, unsigned char led_brightness)
{
	if(led_pos>3) led_pos=3;
	if(led_brightness>7) led_brightness=7;
	
	unsigned char data_TM1637;
	unsigned char pos_TM1637;
	unsigned char brightness_TM1637;

	data_TM1637=digitToSegment[value];
	
	//page 5 datasheet
	pos_TM1637=led_pos | 0xC0;
	
	//page 5 datasheet
	if(led_status==1) //ON LED
		brightness_TM1637=led_brightness | 0x88;
	else brightness_TM1637=led_brightness | 0x80;
	
	//Data setting: fixed address (page 4 datasheet)
	TM1637_Start();
	TM1637_Write(0x44);
	TM1637_Stop();
	
	//Chose LED (page 5 datasheet)
	TM1637_Start();
	TM1637_Write(pos_TM1637);
		
	//Tranfer Data
	TM1637_Write(data_TM1637);
	TM1637_Stop();
	
	//Display LED from Data
	TM1637_Start();
	TM1637_Write(brightness_TM1637);
	TM1637_Stop();
}
