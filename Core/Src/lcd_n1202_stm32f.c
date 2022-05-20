//2022-04-11
//bonusoid

#include "main.h"
#include "lcd_n1202_stm32f.h"

void lcdn1202_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure GPIO pin Output Level
	HAL_GPIO_WritePin(LCDP, LCDBL|LCDDAT|LCDCLK, GPIO_PIN_RESET);

	// Configure GPIO pins
	GPIO_InitStruct.Pin = LCDBL|LCDDAT|LCDCLK;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LCDP, &GPIO_InitStruct);
}

void lcdn1202_9bsend(unsigned char cdsign, unsigned char comdat)
{
	unsigned char cdi;

	if(cdsign==0) HAL_GPIO_WritePin(LCDP, LCDDAT, GPIO_PIN_RESET); //1st bit is 0 for Command
	else HAL_GPIO_WritePin(LCDP, LCDDAT, GPIO_PIN_SET); //1st bit is 1 for Data
	lcdn1202_clock1();

	for(cdi=0;cdi<8;cdi++) //Send 2nd-9th bit
	   {
		if(comdat & 0x80) HAL_GPIO_WritePin(LCDP, LCDDAT, GPIO_PIN_SET); //LCDDAT = '1'
		else HAL_GPIO_WritePin(LCDP, LCDDAT, GPIO_PIN_RESET); //LCDDAT = '0'
		lcdn1202_clock1();
		comdat <<= 1; //Shift to next bit
	   }
	HAL_GPIO_WritePin(LCDP, LCDDAT, GPIO_PIN_RESET); //Reset pin state
}

void lcdn1202_clock1()
{
	HAL_GPIO_WritePin(LCDP, LCDCLK, GPIO_PIN_SET);	//Send 1 pulse to LCDCLK 
	__asm__("nop"); //Short delay
	HAL_GPIO_WritePin(LCDP, LCDCLK, GPIO_PIN_RESET);
}

void lcdn1202_blon()
{
	HAL_GPIO_WritePin(LCDP, LCDBL, GPIO_PIN_SET);	//LCDBL = '1'
}

void lcdn1202_bloff()
{
	HAL_GPIO_WritePin(LCDP, LCDBL, GPIO_PIN_RESET);	//LCDBL = '0'
}
