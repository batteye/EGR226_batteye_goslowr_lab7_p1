/*******************************************************
* Name:                Emily Battey and Rebecca Goslow
* Course:            EGR 226 - Microcontroller Programming and Applications
* Project:            Lab 07 - Interfacing a 4x16 LCD to a MSP432
* Description:        LCD screen functions
*******************************************************/
//libraries
#include "LCD.h"
#include "msp.h"

/***| void LCD_innit() |************************************//*
*Brief:    initializes the LCD .

********************************************************/
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

/***| void write_command() |************************************//*
*Brief:    write a command to the LCD.

********************************************************/
void write_command(uint8_t command){
    LCD->OUT &=~ RS;//set to command mode
    push_byte(command);

}

/***| void push_byte(uint8_t byte) |************************************//*
*Brief:    push a byte of data split into nibbles.
Input: uint8_t byte     the byte to output to the LCD
********************************************************/
void push_byte(uint8_t byte){
    push_nibble((byte & 0xF0)>>4);//first section
    push_nibble(byte & 0x0F);//2nd section
}

/***| void innit_pins() |************************************//*
*Brief:    innitialize the LCD pins.
********************************************************/
void innit_pins(){
    LCD -> SEL0 = 0x00;
        LCD -> SEL1 = 0x00;
    LCD -> DIR |=(RS|E|D4|D5|D6|D7);//all output
    LCD->OUT &=~ D4;
    LCD->OUT &=~ D5;
    LCD->OUT &=~ D6;
    LCD->OUT &=~ D7;
    LCD->OUT &=~ E;//low
    Systick_ms_delay(100);

}

/***| void space(int i) |************************************//*
*Brief:    print i spaces to the console.
Input: int i     number of spaces to print
********************************************************/
void space(int i){
    int x = 0;
    for(x = 0; x < i; x++){
            write_command(0b00010100);//space
        }
}

/***| void push_nibble(uint8_t byte) |************************************//*
*Brief:    push a nibble of data to the LCD.
Input: uint8_t byte     the nibble to output to the LCD
********************************************************/
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
            Systick_us_delay(100);
    PulseEnablePin();
    //The Enable (E) pin is pulsed by making E low for 10µs, then making E high for 10µs and then making
    //E low for at least 10 µs (or more).
    Systick_ms_delay(100);
}


/***| void PusleEnablePin() |************************************//*
*Brief:    pulse the enable pin to transmit data to the LCD
********************************************************/
void PulseEnablePin (){
    LCD->OUT &=~ E;
    Systick_us_delay(10);
    LCD->OUT |= E;
    Systick_us_delay(10);
    LCD->OUT &=~ E;
    Systick_us_delay(100);


}

/***| void Systick_ms_delay(int j)|************************************//*
*Brief:    delay a user set number of milliseconds
Input: int j     the delay in ms
********************************************************/
void Systick_ms_delay(int j){
    //volatile uint32_t i;
    SysTick->LOAD = 3000*j-1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= BIT2|BIT0;  //Turns the timer on
    while(!(SysTick->CTRL & 0x00010000));
    SysTick->CTRL = 0;             //Turn off SysTick

}


/***| void Systick_us_delay(int j)|************************************//*
*Brief:    delay a user set number of microseconds
Input: int j     the delay in us
********************************************************/
void Systick_us_delay(int j){
    //volatile uint32_t i;
    SysTick->LOAD = 3*j-1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= BIT2|BIT0;  //Turns the timer on
    while(!(SysTick->CTRL & 0x00010000));
    SysTick->CTRL = 0;             //Turn off SysTick

}

/***| void dataWrite (uint8_t data)|************************************//*
*Brief:    write data to the LCD screen
Input: uint8_t data     data to write to the LCD
********************************************************/
void dataWrite (uint8_t data){
    LCD->OUT |= RS;//set to write mode
    push_byte(data);
}



