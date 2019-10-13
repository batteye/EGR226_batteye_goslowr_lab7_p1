/*******************************************************
* Name:                Emily Battey and Rebecca Goslow
* Course:            EGR 226 - Microcontroller Programming and Applications
* Project:            Lab 07 - Interfacing a 4x16 LCD to a MSP432
* Description:        print users names to the LCD and the EGR 266 centered
*******************************************************/
#include "msp.h"
#include "LCD.h"
//#include "LCD.c"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	innit_pins();
	LCD_innit();
	write_command(0b00001111);//display on/ cursor on/ blink cursor
	while(1){
	    //no
	}
}
