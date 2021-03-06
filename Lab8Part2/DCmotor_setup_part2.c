#include <TimerLib_part2.h>
#include "msp.h"

void Setup_Init(int duty){
    //Configuring P6.7 for PWM Output
    P6SEL0 |= BIT7;
    P6SEL1 &= ~BIT7;
    P6DIR |= BIT7;

    //TimerA setup for PWM with variable duty cycle
    TIMER_A2->CCR[0] = 37500;
    TIMER_A2->CCR[4] = duty;
    TIMER_A2->CCTL[4] = 0xE0;
    TIMER_A2->CTL = 0x0254;
}
void MotorSpeed(double x){
    int duty=37500*x;
    Setup_Init(duty);
}
