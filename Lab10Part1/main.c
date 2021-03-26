#include "msp.h"
#include<stdio.h>
double convertV(double x);
void adcsetup(void);
void delay_ms(int n);
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    double x =0 ,volt=0;
    adcsetup();

    while(1){
    ADC14->CTL0 |=1; //start a conversion
    while(!ADC14->IFGR0); // wait until conversion complete
    x = ADC14->MEM[5]; // immediately store value in a variable
    volt = convertV(x);
    printf("test raw value:\t%f\n", x);
    printf("test voltage: \t%f\n", volt);
    delay_ms(1500); // wait for next value- using Systick function
    }
}
double convertV(double x){
double voltage;
voltage = x*0.0002;
return voltage;
}

void adcsetup(void)
{
    ADC14->CTL0 = 0x00000010; //power on and disabled during configuration
    ADC14->CTL0 |= 0x04D80300; // S/H pulse mode, MCLCK, 32 sample clocks, sw trigger, /4 clock divide
    ADC14->CTL1 = 0x00000030; // 14-bit resolution
    ADC14->MCTL[5] = 0; // A0 input, single ended, vref=avcc
    P5SEL1 |= 0x20; // configure pin 5.5 for AO
    P5SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000; //start converting at mem reg 5
    ADC14->CTL0 |= 2; //enable ADC after configuration
}
void delay_ms(int n){
    int i;
    SysTick->LOAD=(3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;

    for(i=0;i<n;i++){
        while((SysTick->CTRL & BIT(16))==0);
    }
    SysTick->CTRL=0;
}
