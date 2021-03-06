#include <FuncLibPart3.h>
#include "msp.h"


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
    P2OUT &=~0xF0; // clear P2.4-P2.7
    P2OUT |= (nibble & 0x0F) << 4; // port pins P2.4 - P2.7 wired to D4 - D7
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


void adcsetup(void)
{
    ADC14->CTL0 = 0x00000010; //power on and disabled during configuration
    ADC14->CTL0 |= 0x04D80300; // S/H pulse mode, MCLCK, 32 sample clocks, sw trigger, /4 clock divide
    ADC14->CTL1 = 0x00000030; // 14-bit resolution
    ADC14->MCTL[5] = 0; // A0 input, single ended, vref=avcc
    P5SEL1 |= 0x20; // configure pin 5.5 for A0
    P5SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000; //start converting at mem reg 5
    ADC14->CTL0 |= 2; //enable ADC after configuration
}

void PrintChar(void){
    int i;
    char arr[7]={'T','E','M','P',':',0xDF,'C'};
    write_command(6); //entry mode
    for(i=0;i<7;i++)
        write_data(arr[i]);

}

void UpdateTemp(double t){
    int i;
    char Temp[4];
    sprintf(Temp, "%.1f",t);

    write_command(6); //entry mode
    for(i=0;i<4;i++)
        if(Temp[3]==0)
            write_data(0x20);
        else
            write_data(Temp[i]);

}
