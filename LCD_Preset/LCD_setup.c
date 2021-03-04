#include "LCD_preset.h"
#include "msp.h"
void LCD_init (void){
    //initialize data pins P2.4 - 2.7, check lab sheet for proper process
    P4SEL1 = 0x00;
    P4SEL0 = 0x00;
    P4DIR = 0x00;
    P4REN = (BIT4 | BIT5 | BIT6 | BIT7);
    P4OUT = (BIT4 | BIT5 | BIT6 | BIT7);

    //initialize LCD
    write_command(3);
    Systick_ms_delay(100);
    write_command(3);
    Systick_us_delay(200);
    write_command(3);
    Systick_ms_delay(100);
    write_command(2);
    Systick_us_delay(100);
    write_command(0x28);
    Systick_us_delay(100);
    Systick_us_delay(100);
    write_command(0x0F);
    Systick_us_delay(100);
    write_command(0x01);
    Systick_us_delay(100);
    write_command(0x06);
    Systick_ms_delay(10);
}
void PulseEnablePin (void){
    P4OUT &=~BIT2;
    Systick_us_delay(10);
    P4OUT |=BIT2;
    Systick_us_delay(10);
    P4OUT &=~BIT2;
    Systick_us_delay(10);
}
void pushNibble (int nibble){
    P4OUT &=~0xF0; // clear P4.4-P4.7
    P4OUT |= (nibble & 0x0F) << 4; // port pins P4.4 - P4.7 wired to D4 - D7
    PulseEnablePin();
}
void pushByte (int byte){
    int nibble;
    nibble = (byte & 0xF0) >> 4;
    pushNibble(nibble);
    nibble = byte & 0x0F;
    pushNibble(nibble);
    Systick_us_delay(100);
}
void write_command (int command){
    pushByte(command);
}
void write_data (int data){
    pushByte(data);
}
void Systick_us_delay(int n){
    SysTick->LOAD=(n*3-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;
    while((SysTick->CTRL & BIT(16))==0);
    SysTick->CTRL=0;
}
void Systick_ms_delay(int n){
    SysTick->LOAD=(n*3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;
    while((SysTick->CTRL & BIT(16))==0);
    SysTick->CTRL=0;
}
