/*
 * LCD.h
 *
 *  Created on: Oct 9, 2019
 *      Author: ekbat
 */

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

void LCD_innit();
void innit_pins();
void write_command(volatile uint8_t command);
void push_byte(volatile uint8_t byte);
void push_nibble(volatile uint8_t nibble);
void PulseEnablePin();
void Systick_ms_delay(int j);
void Systick_us_delay(int j);


#endif /* LCD_H_ */
