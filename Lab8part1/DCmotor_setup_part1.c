#include <TimerLib_part1.h>
#include "msp.h"

void Setup_Init(void){

        //P1.6 init
        P1SEL1 = 0x00;
        P1SEL0 = 0x00;
        P1DIR |= BIT6;
  //      P3REN &= ~BIT6;
    //    P3OUT &= ~BIT6;
}
void Systick_ms_delay(int n){
    SysTick->CTRL=0;
    SysTick->LOAD=(n*3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x05;
    while((SysTick->CTRL & BIT(16))==0);
}
void Systick_DutyCycle(double n){
    double p = 25, Ton, Toff;
    //n = on/off, run at 40Hz by default
    Ton = n*p;
    Toff = p-Ton;
    Systick_ms_delay(Ton);
    P1OUT &= ~BIT6;
    Systick_ms_delay(Toff);
}
void Systick_MotorSpeed(void){
    double x=1;
    P1OUT |= BIT6;
    Systick_DutyCycle(x);       //enter number between 0 and 1
}
