#include "msp.h"
#include "stdio.h"

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

void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(375000-1);      //half-second delay between displaying numbers
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}

void SysTick_Handler(void) {
    blocked=1;
}
