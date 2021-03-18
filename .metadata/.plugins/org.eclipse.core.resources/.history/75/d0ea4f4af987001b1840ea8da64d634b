#include <TimerLib_part2.h>
#include "msp.h"

void Setup_Init(void){
    //Configuring P2.7 for PWM Output
    P2SEL1 |= BIT7;
    P2SEL0 &= ~BIT7;
    P2DIR |= BIT7;


    //test config timer A for 40% duty cycle
    TIMER_A0->CCR[0] = 75000;
    TIMER_A0->CCR[4] = 30000;
    TIMER_A0->CCTL[4] = 0xE0;
    TIMER_A0->CTL = 0x0214;
}
void MotorSpeed(void){
    double duty,x=1;
    duty=75000*x;
    TIMER_A0->CCR[0] = 75000;
    TIMER_A0->CCR[4] = duty;
    TIMER_A0->CCTL[4] = 0x70;
    TIMER_A0->CTL = 0x0214;
}
