/****************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 04/02/2021
 * Project: Lab 10 Part 2
 * File: part2main.c
 * Description: This code takes the voltage from the TMP36 and prints the 
 * temperature in celsius and fahrenheit to the console window
 ****************************************************************************/
#include "msp.h"
#include<stdio.h>

volatile int flag=0;
void SysTick_Init_interrupt(void);
void adcsetup(void);
void delay_ms(int n);
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    adcsetup();
    SysTick_Init_interrupt();
    __enable_interrupt();
    double x, Celsius, volt, Fahren;
    while(1){
        if(flag){
            ADC14->CTL0 |=1;
            while(!ADC14->IFGR0);

            x = ADC14->MEM[5];
            volt = x*0.0002;
            Celsius = (volt*1000-500)/10;
            Fahren = Celsius*1.8+32;

            printf("Temperature in Celcius:\t%f\n", Celsius);
            printf("Temperature in Fahrenheit:\t%f\n", Fahren);

            flag=0;
        }
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
    ADC14->CTL0 = 0x00000010; //power on and disabled during configuration
    ADC14->CTL0 |= 0x04D80300; // S/H pulse mode, MCLCK, 32 sample clocks, sw trigger, /4 clock divide
    ADC14->CTL1 = 0x00000030; // 14-bit resolution
    ADC14->MCTL[5] = 0; // A0 input, single ended, vref=avcc
    P5SEL1 |= 0x20; // configure pin 5.5 for A0
    P5SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000; //start converting at mem reg 5
    ADC14->CTL0 |= 2; //enable ADC after configuration
}
/****| SysTick_Init_interrupt | *****************************************
 * Brief: Initializes SysTick to delay for a half second then interrupt
 * param: void
 * return: void
 *************************************************************/
void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(1500000-1);      //half-second delay between displaying numbers
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}

void SysTick_Handler (void) {
    flag=1;
}
