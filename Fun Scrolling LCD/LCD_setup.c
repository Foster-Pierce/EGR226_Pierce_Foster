#include "LCD_preset.h"
#include "msp.h"
//sheesh ur cool
char arr[]={'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};

void LCD_init (void){
    //initialize data pins P2.4 - 2.7
    P2SEL1 = 0x00;
    P2SEL0 = 0x00;
    P2DIR |= (BIT4 | BIT5 | BIT6 | BIT7);
    P2REN &= ~(BIT4 | BIT5 | BIT6 | BIT7);
    P2OUT |= (BIT4 | BIT5 | BIT6 | BIT7);

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
    write_command(0x0C);
    Systick_us_delay(100);
    write_command(0x01);
    Systick_us_delay(100);
    write_command(0x06);
    Systick_ms_delay(10);
}
void PulseEnablePin (void){
    P5OUT &=~BIT0;
    Systick_us_delay(10);
    P5OUT |=BIT0;
    Systick_us_delay(10);
    P5OUT &=~BIT0;
    Systick_us_delay(10);
}
void pushNibble (int nibble){
    P2OUT &=~0xF0; // clear P2.4-P2.7
    P2OUT |= (nibble & 0x0F) << 4; // port pins P2.4 - P2.7 wired to D4 - D7
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
    P5OUT |= BIT2;
    pushByte(data);
    P5OUT &= ~BIT2;
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
void PrintChar(void){
    int i,j;
    write_command(6); //entry mode
    for(j=0;j<16;j++){
        for(i=0;i<16-j;i++){
            if (arr[i+j]==0)
                write_data(0x20);
                else
                    write_data(arr[i+j]);
        }
        Systick_ms_delay(750);
        write_command(0x80);
    }
}
