#include <TimerLib_part3.h>
#include "msp.h"

void Setup_Init(int duty){
    //Configuring P2.7 for PWM Output
    P2SEL1 |= BIT7;
    P2SEL0 &= ~BIT7;
    P2DIR |= BIT7;

    //Config for TimerA with variable duty cycle
    TIMER_A0->CCR[0] = 37500;
    TIMER_A0->CCR[4] = duty;
    TIMER_A0->CCTL[4] = 0xE0;
    TIMER_A0->CTL = 0x0254;
}
void MotorSpeed(double x){
    int duty=37500*x;
    Setup_Init(duty);
}

void Keypad_init(void){
    //Configure GPIO ROWS: P4 .0 .1 .2 .3 & COL: P4 .4 .5 .6

    //Configure ROWS
    P4SEL1 = 0x00;
    P4SEL0 = 0x00;
    P4DIR = 0x00;
    P4REN = (BIT0 | BIT1 | BIT2 | BIT3);
    P4OUT = (BIT0 | BIT1 | BIT2 | BIT3);

    //Configure COLUMNS
    P4REN &= ~(BIT4 | BIT5 | BIT6);
    P4OUT &= ~(BIT4 | BIT5 | BIT6);
}

int Keypad_Read(void){
    int col, row, num;
    for (col = 0; col < 3; col++)
    {
        P4DIR = 0x00; //set columns to inputs
        P4DIR |= BIT (4+col); //set column 0 to output
        P4OUT &=~ BIT (4+col); //set column 0 to LOW

        SysTick_ms_delay(10);
        row = P4IN & 0x0F; //read rows
        SysTick_ms_delay(10);

        while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );

        if (row != 0x0F) break; // if one of the input is low, some key is pressed.
    }

    P4DIR = 0x00; // Set Columns to inputs
    if (col == 3)
        return 0;

    if (row == 0x0E) num = col + 1; // key in row 0
    if (row == 0x0D) num = 3 + col +1; // key in row 1
    if (row == 0x0B) num = 6 + col +1; // key in row 2
    if (row == 0x07) num = 9 + col+1; // key in row 3

    return num;
}

void SysTick_ms_delay(int n){
    int i;
    SysTick->LOAD=(3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;

    for(i=0;i<n;i++){
        while((SysTick->CTRL & BIT(16))==0);
    }

    SysTick->CTRL=0;

}

int Press_Convert(int n){
    int DC;
    if((n<=9)&&(n>0)){
        DC=n/10;
        return DC;
    }
    else if(n==10)
        return n;
    else if(n==11)
        return 0;
    else if(n==12)
        return 0;

    return 0;
}
