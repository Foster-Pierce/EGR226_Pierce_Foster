#include <TimerLib_part2.h>
#include "msp.h"

void Setup_Init(int duty){
    //Configuring P2.7 for PWM Output
    P2SEL1 |= BIT7;
    P2SEL0 &= ~BIT7;
    P2DIR |= BIT7;

    //test config timer A for ~50% duty cycle
    TIMER_A0->CCR[0] = 37500;
    TIMER_A0->CCR[4] = duty;
    TIMER_A0->CCTL[4] = 0xE0;
    TIMER_A0->CTL = 0x0254;
}
void MotorSpeed(double x){
    int duty=37500*x;
    Setup_Init(duty);
}
