#include <TimerLib_part1.h>
#include "msp.h"

void Setup_Init(void){

        //P2.6 init
        P2SEL1 = 0x00;
        P2SEL0 = 0x00;
        P2DIR |= BIT6;
        P2REN &= ~BIT6;
        P2OUT &= ~BIT6;
}
void Systick_us_delay(int n){
    SysTick->LOAD=(n*3-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;
    while((SysTick->CTRL & BIT(16))==0);
    SysTick->CTRL=0;
}
void Systick_DutyCycle(double n){
    int p = 25000, Ton, Toff;
    //n = on/off, run at 40Hz by default
    Ton = n*p;
    Toff = p-Ton;
    Systick_us_delay(Toff);
}
void Systick_MotorSpeed(void){
    //turn on, wait, turn off, wait, repeat
    int x=0;
    P2OUT |= BIT6;
    Systick_DutyCycle(x);
    P2OUT &= ~BIT6;
    Systick_DutyCycle(x);

}