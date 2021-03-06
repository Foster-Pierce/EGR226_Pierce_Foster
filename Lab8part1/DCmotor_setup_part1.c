#include <TimerLib_part1.h>
#include "msp.h"

void Setup_Init(void){
    //P3.0 init
    P3SEL1 = 0x00;
    P3SEL0 = 0x00;
    P3DIR |= BIT0;
}
void Systick_ms_delay(int n){
    SysTick->CTRL=0;
    SysTick->LOAD=(n*3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x05;
    while((SysTick->CTRL & BIT(16))==0);
}
void Systick_DutyCycle(double n){
    int p = 25;     //period
    int Ton, Toff;

    Ton = n*p;      //time on
    Toff = p-Ton;   //time off
    P3OUT |= BIT0;
    if(Ton!=0)
        Systick_ms_delay(Ton);
    P3OUT &= ~BIT0;
    if(Toff!=0)
        Systick_ms_delay(Toff);
}
