#include <LCD_preset_part2.h>
#include "msp.h"

const char arr[4][6]={
{'P','I','E','R','C','E'},
{'F','O','S','T','E','R'},
{'E','G','R',' ', ' ', ' '},
{'2','2','6',' ', ' ', ' '}
};

void LCD_init (void){
    //initialize data pins P2.4 - 2.7
    P8SEL1 = 0x00;
    P8SEL0 = 0x00;
    P8DIR |= (BIT4 | BIT5 | BIT6 | BIT7);
    P8REN &= ~(BIT4 | BIT5 | BIT6 | BIT7);
    P8OUT |= (BIT4 | BIT5 | BIT6 | BIT7);


    //initialize RS and E on P5.2 & P5.0
    P5SEL1 = 0x00;
    P5SEL0 = 0x00;
    P5DIR |= (BIT2 | BIT0);
    P5REN &= ~(BIT2 | BIT0);
    P5OUT &= ~(BIT2 | BIT0);
    Systick_ms_delay(60);


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
    write_command(0x0F);
    Systick_us_delay(100);
    write_command(0x01);
    Systick_us_delay(100);
    write_command(0x06);
    Systick_ms_delay(10);
}
void PulseEnablePin (void){
    P5OUT &=~BIT0;          //pulse low for 10us
    Systick_us_delay(10);
    P5OUT |=BIT0;           //pulse high for 10us
    Systick_us_delay(10);
    P5OUT &=~BIT0;          //pulse low for 10us
    Systick_us_delay(10);
}
void pushNibble (int nibble){
    P8OUT &=~0xF0; // clear P2.4-P2.7
    P8OUT |= (nibble & 0x0F) << 4; // port pins P2.4 - P2.7 wired to D4 - D7
    PulseEnablePin();
}
void pushByte (int byte){
    int nibble;                     //splitting the byte into 4 bit chunks
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
    P5OUT |= BIT2;          //Sets RS
    pushByte(data);
    P5OUT &= ~BIT2;         //clears RS
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
void PrintChar(int c){
    int i;
    write_command(6); //entry mode
    for(i=0;i<6;i++)
        write_data(arr[c][i]);

}
