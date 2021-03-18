#include <TimerLib_part1.h>
#include "msp.h"

void Setup_Init(void){
    //P1.6 init
    P1SEL1 = 0x00;
    P1SEL0 = 0x00;
    P1DIR |= BIT6;
}
void Systick_ms_delay(int n){
    SysTick->CTRL=0;
    SysTick->LOAD=(n*3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x05;
    while((SysTick->CTRL & BIT(16))==0);
}
void Systick_DutyCycle(double n){
    int p = 25;
    int Ton, Toff;

    Ton = n*p;
    Toff = p-Ton;
    Systick_ms_delay(Ton);
    P1OUT &= ~BIT6;
    if(Toff!=0)
        Systick_ms_delay(Toff);
    else{}
}
void Systick_MotorSpeed(double x){
    P1OUT |= BIT6;
    Systick_DutyCycle(x);
}
