//2022-04-11
//bonusoid

#ifndef __LCD_N1202_STM32F_H
#define __LCD_N1202_STM32F_H

#define LCDN1202_COL	96	//96 columns
#define LCDN1202_ROW	9	//8,5 rows (8 byte and 1 nibble)

#define LCDDAT 	GPIO_PIN_8	//LCD DATA
#define LCDCLK 	GPIO_PIN_9	//LCD CLOCK
#define LCDBL	GPIO_PIN_7	//LCD BACKLIGHT CONTROL
#define LCDP 	GPIOA		//LCD GPIO PORT

//LCD Hardware Access Functions
void lcdn1202_gpio_init(); //LCD Interface Initialization
void lcdn1202_9bsend(unsigned char cdsign, unsigned char comdat); //Send 9 bit Command/Data to LCDDAT
void lcdn1202_clock1(); //Send clock pulse to LCDCLK
void lcdn1202_blon();	//LCDBL = '1'
void lcdn1202_bloff();	//LCDBL = '0'

#endif
