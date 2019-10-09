/*
 * LCD.c
 *
 *  Created on: Oct 9, 2019
 *      Author: ekbat
 */

#include "LCD.h"
#include "msp.h"

void LCD_innit(){
write_command(0x30);
 Systick_ms_delay(100);
 write_command(0x30);
 Systick_us_delay(200);
 write_command(0x30);
 Systick_ms_delay(100);
 write_command(2);
 Systick_us_delay(100);
 write_command(2);
 Systick_us_delay(100);
 write_command(8);//00001111
 Systick_us_delay(100);
 write_command(0x0F);
 Systick_us_delay(100);
 write_command(1);
 Systick_us_delay(100);
 write_command(6);
 Systick_ms_delay(10);
}

void write_command(uint8_t command){
    LCD->OUT &=~ RS;//set to command mode
    push_byte(command);

}

void push_byte(uint8_t byte){
    push_nibble(byte & 0xF0);
    push_nibble(byte & 0x0F);
}

void innit_pins(){
    LCD -> SEL0 = 0x00;
        LCD -> SEL1 = 0x00;
    LCD -> DIR |=(RS|E|D4|D5|D6|D7);//all output
    LCD->OUT &=~ D4;
    LCD->OUT &=~ D5;
    LCD->OUT &=~ D6;
    LCD->OUT &=~ D7;
    LCD->OUT &=~ E;

}

void push_nibble(uint8_t nibble){
    LCD->OUT &=~ D4;
    LCD->OUT &=~ D5;
    LCD->OUT &=~ D6;
    LCD->OUT &=~ D7;
    volatile uint8_t a = 0x08 & nibble;
    if(a > 0){
       LCD -> OUT |= D7;
    }
    a = 0x04 & nibble;
    if(a > 0){
           LCD ->OUT |= D6;
        }
    a = 0x02 & nibble;
        if(a > 0){
           LCD ->OUT |= D5;
        }
        a = 0x01 & nibble;
            if(a > 0){
           LCD -> OUT |= D4;
        }

    PulseEnablePin();
    //The Enable (E) pin is pulsed by making E low for 10µs, then making E high for 10µs and then making
    //E low for at least 10 µs (or more).
    Systick_ms_delay(100);
}
void PulseEnablePin (){
    LCD->OUT &=~ E;
    Systick_us_delay(10);
    LCD->OUT |= E;
    Systick_us_delay(10);
    LCD->OUT &=~ E;
    Systick_us_delay(10);


}

void Systick_ms_delay(int j){
    //volatile uint32_t i;
    SysTick->LOAD = 3000*j-1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= BIT2|BIT0;  //Turns the timer on
    while(!(SysTick->CTRL & 0x00010000));
    SysTick->CTRL = 0;             //Turn off SysTick

}

void Systick_us_delay(int j){
    //volatile uint32_t i;
    SysTick->LOAD = 3*j-1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= BIT2|BIT0;  //Turns the timer on
    while(!(SysTick->CTRL & 0x00010000));
    SysTick->CTRL = 0;             //Turn off SysTick

}



