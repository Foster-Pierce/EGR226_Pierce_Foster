/****************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 04/08/2021
 * Project: Lab 11
 * File: part1main.c
 * Description: This program detects when the IR receiver is detecting a 10 Hz
 * frequency, and turns the onboard LED on. When this signal is blocked, the 
 * light turns off, and this process can repeat forever.
 ****************************************************************************/
#include "msp.h"
volatile int edge0, edge1, period, flag10, blocked;
void SysTick_Init_interrupt(void);
void setup_init(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    setup_init();
    NVIC_EnableIRQ(TA0_N_IRQn);
    __enable_interrupt();

    while(1){
        if(flag10){
            P2OUT |= BIT0;
            flag10=0;
        }
        else if(blocked){
            P2OUT &=~ BIT0;
            blocked=0;
        }
    }
}
/****| setup_init | *****************************************
 * Brief: Initializes the seven segment display
 * param: void
 * return: void
 *************************************************************/
void setup_init(void){
    //Configuring P6.7 for PWM Output
    P6SEL0 |= BIT7;
    P6SEL1 &= ~BIT7;
    P6DIR |= BIT7;

    //Configuring P2.4 for capture
    P2SEL0 |= BIT4;
    P2SEL1 &= ~BIT4;
    P2DIR &=~ BIT4;

    //test led
    P2->DIR = BIT0;

    //TimerA2.4 setup for PWM
    TIMER_A2->CCR[0] = 37500;           // 10Hz
    TIMER_A2->CCR[4] = 37500/2;         // 50% duty cycle
    TIMER_A2->CCTL[4] = 0xE0;
    TIMER_A2->CTL = 0x02D4;

    //TimerA0.1 setup for capture
    TIMER_A0->CTL = 0x0224;
    TIMER_A0->CCTL[1] = 0x4910;

}
/****| TA0_N_IRQHandler | *****************************************
 * Brief: ISR for TimerA capture, which determines the period
 * and sets a flag if the signal is being received, else if the
 * signal is blocked, the interrupt for SysTick will trigger
 * param: void
 * return: void
 *************************************************************/
void TA0_N_IRQHandler(void){

    if(TIMER_A0->CCTL[1]&BIT0){
        edge1 = TIMER_A0->CCR[1];
        period = edge1 - edge0;
        edge0 = edge1;
        if ((32000<period) && (period<43000))
            flag10=1;

        TIMER_A0->CCTL[1] &=~ (BIT0 | BIT1);
        SysTick_Init_interrupt();
    }
}
/****| SysTick_Init_interrupt | *****************************************
 * Brief: Initializes SysTick to delay for a 1/8 second then interrupt
 * param: void
 * return: void
 *************************************************************/
void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(375000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}
/****| SysTick_Handler | *****************************************
 * Brief: SysTick ISR, that updates blocked flag when the signal
 * is no longer being received
 * param: void
 * return: void
 *************************************************************/
void SysTick_Handler(void) {
    blocked=1;
}
