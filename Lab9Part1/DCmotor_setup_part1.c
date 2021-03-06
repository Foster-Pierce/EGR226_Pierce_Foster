#include <TimerLib_part1.h>
#include "msp.h"
volatile double DC=0;

void Setup_Init(int duty){
    //Configuring P6.7 for PWM Output
    P6SEL0 |= BIT7;
    P6SEL1 &= ~BIT7;
    P6DIR |= BIT7;

    P4SEL1 &= ~BIT2; // configure P4.2 as simple I/O SWITCH 1 (RED)
    P4SEL0 &= ~BIT2;
    P4DIR &= ~BIT2;
    P4REN |= BIT2;
    P4OUT |= BIT2;
    P4IES |= BIT2;
    P4IE |= BIT2;
    P4IFG = 0;

    P4SEL1 &= ~BIT3; // configure P4.3 as simple I/O SWITCH 2 (GREEN)
    P4SEL0 &= ~BIT3;
    P4DIR &= ~BIT3;
    P4REN |= BIT3;
    P4OUT |= BIT3;
    P4IES |= BIT3;
    P4IE |= BIT3;
    P4IFG = 0;

    P4SEL1 &= ~BIT1; // configure P4.1 as simple I/O SWITCH 2 (BLUE)
    P4SEL0 &= ~BIT1;
    P4DIR &= ~BIT1;
    P4REN |= BIT1;
    P4OUT |= BIT1;
    P4IES |= BIT1;
    P4IE |= BIT1;
    P4IFG = 0;

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

void PORT4_IRQHandler (void){   // port 4 service routine
    if (P4IFG & BIT3){          // check if green had interrupt
        if ((DC>=0) & (DC<=1))
            DC += .1;
        else
            DC=1;
        MotorSpeed(DC);         // change motor speed
        P4IFG &= ~BIT3;         // turn off flag
    }
    else if (P4IFG & BIT1){      // check if blue had interrupt
        if ((DC>0) & (DC<1))
            DC -= .1;
        else
            DC=0;
        MotorSpeed(DC);
        P4IFG &= ~BIT1;
    }
    else if (P4IFG & BIT2){      // check if red had interrupt
        DC = 0;
        MotorSpeed(DC);
        P4IFG &= ~BIT2;
    }
    else
        P4IFG=0;
}

