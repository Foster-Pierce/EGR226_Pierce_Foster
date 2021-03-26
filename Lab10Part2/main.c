#include "msp.h"
#include<stdio.h>

void SysTick_Init_interrupt(void);
double convertV(double x);
double convertT(double x);
double convertT2(double x);
void adcsetup(void);
void delay_ms(int n);
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    adcsetup();
    SysTick_Init_interrupt();
    __enable_interrupt();

    while(1){
    }
}

double convertV(double x){
    double voltage;
    voltage = x*0.0002;
    return voltage;
}

double convertT(double x){
    double temp;
    temp = (x*1000-500)/10;
    return temp;
}

double convertT2(double x){
    double temp;
    temp = x*1.8+32;
    return temp;
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
void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(1500000-1);      //half-second delay between displaying numbers
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}

void SysTick_Handler (void) {
    double x =0, Celsius=0, volt=0, Fahren=0;

    ADC14->CTL0 |=1;
    while(!ADC14->IFGR0);

    x = ADC14->MEM[5];
    volt = convertV(x);
    Celsius = convertT(volt);
    Fahren = convertT2(Celsius);

    printf("Temperature in Celcius:\t%f\n", Celsius);
    printf("Temperature in Fahrenheit:\t%f\n", Fahren);
}