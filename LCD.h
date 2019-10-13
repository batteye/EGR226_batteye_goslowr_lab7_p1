/*******************************************************
* Name:                Emily Battey and Rebecca Goslow
* Course:            EGR 226 - Microcontroller Programming and Applications
* Project:            Lab 07 - Interfacing a 4x16 LCD to a MSP432
* Description:        function definitions for the LCD library
*******************************************************/

#ifndef LCD_H_
#define LCD_H_
#include "msp.h"
#define LCD P4
#define RS BIT1
#define E BIT3
#define D4 BIT0
#define D5 BIT2
#define D6 BIT4
#define D7 BIT5

void space(int i);
void LCD_innit();
void innit_pins();
void write_command(volatile uint8_t command);
void push_byte(volatile uint8_t byte);
void push_nibble(volatile uint8_t nibble);
void PulseEnablePin();
void Systick_ms_delay(int j);
void Systick_us_delay(int j);
void dataWrite(volatile uint8_t data);


#endif /* LCD_H_ */
