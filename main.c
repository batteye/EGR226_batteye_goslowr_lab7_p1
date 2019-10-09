#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	innit_pins();
	LCD_innit();
	write_command(00001111);//display on/ cursor on/ blink cursor
}
