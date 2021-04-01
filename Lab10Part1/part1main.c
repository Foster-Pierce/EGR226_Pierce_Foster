#include "msp.h"
#include<stdio.h>

void adcsetup(void);
void delay_ms(int n);
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    double x =0 ,volt=0;
    adcsetup();

    while(1){
        ADC14->CTL0 |=1;                        //start conversion
        while(!ADC14->IFGR0);                   // wait until conversion completes
        x = ADC14->MEM[5];                      // stores value in variable
        volt = x*0.0002;
        printf("test raw value:\t%f\n", x);
        printf("test voltage: \t%f\n", volt);
        delay_ms(1000);                         // wait for next value
    }
}
/****| adcsetup | *****************************************
 * Brief: Sets up the ADC for 14-bit resolution and stores
 * information at memory location 5.
 * param: void
 * return: void
 *************************************************************/
void adcsetup(void)
{
    ADC14->CTL0 = 0x00000010;   //power on, start disabled
    ADC14->CTL0 |= 0x04D80300;  // setup clock to mode described in lecture
    ADC14->CTL1 = 0x00000030;   // 14-bit resolution
    ADC14->MCTL[5] = 0;         // A0 input, single ended, vref=avcc
    P5SEL1 |= 0x20;             // configure pin 5.5 for AO
    P5SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000;  //start converting at memory location
    ADC14->CTL0 |= 2;           //enable ADC
}
/****| delay_ms | *****************************************
 * Brief: Initializes SysTick to delay for n amount of time
 * param: int; n, number of milliseconds
 * return: void
 *************************************************************/
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
