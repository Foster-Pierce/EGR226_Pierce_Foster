#include <TimerLib_part3.h>
#include "msp.h"

void Setup_Init(int duty){
    //Configuring P2.7 for PWM Output
    P6SEL0 |= BIT7;
    P6SEL1 &= ~BIT7;
    P6DIR |= BIT7;

    //Config for TimerA with variable duty cycle
    TIMER_A2->CCR[0] = 37500;
    TIMER_A2->CCR[4] = duty;
    TIMER_A2->CCTL[4] = 0xE0;
    TIMER_A2->CTL = 0x0254;
}
void MotorSpeed(double x){
    int duty=37500*x;
    Setup_Init(duty);
}

void Keypad_init(void){
    //Configure GPIO ROWS: P4 .0 .1 .2 .3 & COL: P4 .4 .5 .6

    //Configure ROWS
    P6SEL1 = 0x00;
    P6SEL0 = 0x00;
    P6DIR = 0x00;
    P6REN = (BIT0 | BIT1 | BIT2 | BIT3);
    P6OUT = (BIT0 | BIT1 | BIT2 | BIT3);

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
        row = P6IN & 0x0F; //read rows
        SysTick_ms_delay(10);

        while ( !(P6IN & BIT0) | !(P6IN & BIT1) | !( P6IN & BIT2) | !( P6IN & BIT3) );

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

double Press_Convert(int n){
    if((n<=9)&&(n>0)){          //assigns the key pressed to it's respected duty cycle value
     double DC=(double)n/10;
        return DC;
    }
    else if(n==10)
        return 1;
    else if(n==11)
        return 0;
    else if(n==12)
        return 0;

    return 0;
}
