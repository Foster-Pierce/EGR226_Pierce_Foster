#include <LCD.h>
#include <FuncsLib.h>
#include "msp.h"

//make sure all pwm are initialized corectly
void LCD_init (void){
    //initialize data pins P2.4 - 2.7
    P2SEL1 = 0x00;
    P2SEL0 = 0x00;
    P2DIR |= (BIT4 | BIT5 | BIT6 | BIT7);
    P2REN &= ~(BIT4 | BIT5 | BIT6 | BIT7);
    P2OUT |= (BIT4 | BIT5 | BIT6 | BIT7);

    //initialize RS and E on P5.2 & P5.0
    P5SEL1 = 0x00;
    P5SEL0 = 0x00;
    P5DIR |= (BIT2 | BIT0);
    P5REN &= ~(BIT2 | BIT0);
    P5OUT &= ~(BIT2 | BIT0);
    Systick_ms_delay(60);

    //initialize LCD
    write_command(3);
    Systick_ms_delay(100);
    write_command(3);
    Systick_us_delay(200);
    write_command(3);
    Systick_ms_delay(100);
    write_command(2);
    Systick_us_delay(100);
    write_command(0x28);
    Systick_us_delay(100);
    write_command(0x0F);
    Systick_us_delay(100);
    write_command(0x01);
    Systick_us_delay(100);
    write_command(0x06);
    Systick_ms_delay(10);
}

void Systick_us_delay(int n){
    SysTick->LOAD=(n*3-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;
    while((SysTick->CTRL & BIT(16))==0);
    SysTick->CTRL=0;
}
void Systick_ms_delay(int n){
    SysTick->LOAD=(n*3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;
    while((SysTick->CTRL & BIT(16))==0);
    SysTick->CTRL=0;
}

void adcsetup(void)
{
    ADC14->CTL0 = 0x00000010; //power on and disabled during configuration
    ADC14->CTL0 |= 0x04D80300; // S/H pulse mode, MCLCK, 32 sample clocks, sw trigger, /4 clock divide
    ADC14->CTL1 = 0x00000030; // 14-bit resolution
    ADC14->MCTL[5] = 0; // A0 input, single ended, vref=avcc
    P5SEL1 |= 0x20; // configure pin 5.5 for A0
    P5SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000; //start converting at mem reg 5
    ADC14->CTL0 |= 2; //enable ADC after configuration
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

void Setup_Init(void){
    // configure P3.5 as simple I/O SWITCH 1 RED
    P3SEL1 &= ~BIT5;
    P3SEL0 &= ~BIT5;
    P3DIR &= ~BIT5;
    P3REN |= BIT5;
    P3OUT |= BIT5;
    P3IES |= BIT5;
    P3IE |= BIT5;
    P3IFG = 0;

    // configure P3.6 as simple I/O SWITCH 2 GREEN
    P3SEL1 &= ~BIT6;
    P3SEL0 &= ~BIT6;
    P3DIR &= ~BIT6;
    P3REN |= BIT6;
    P3OUT |= BIT6;
    P3IES |= BIT6;
    P3IE |= BIT6;
    P3IFG = 0;

    // configure P3.7 as simple I/O SWITCH 3 BLUE
    P3SEL1 &= ~BIT7;
    P3SEL0 &= ~BIT7;
    P3DIR &= ~BIT7;
    P3REN |= BIT7;
    P3OUT |= BIT7;
    P3IES |= BIT7;
    P3IE |= BIT7;
    P3IFG = 0;

    // configure P3.2 as simple I/O SWITCH 4 WHITE
    P3SEL1 &= ~BIT2;
    P3SEL0 &= ~BIT2;
    P3DIR &= ~BIT2;
    P3REN |= BIT2;
    P3OUT |= BIT2;
    P3IES |= BIT2;
    P3IE |= BIT2;
    P3IFG = 0;
    // configure P3.3 as simple I/O SWITCH 5 BLACK
    P3SEL1 &= ~BIT3;
    P3SEL0 &= ~BIT3;
    P3DIR &= ~BIT3;
    P3REN |= BIT3;
    P3OUT |= BIT3;
    P3IES |= BIT3;
    P3IE |= BIT3;
    P3IFG = 0;

    //Configuring P6.7 for PWM Output
    P6SEL0 |= BIT7;
    P6SEL1 &= ~BIT7;
    P6DIR |= BIT7;

    //add multiple more timerA for PWM of servo and backlight
}
void MotorConfig(double d){
//Config for TimerA with variable duty cycle
    TIMER_A2->CCR[0] = 37500;
    TIMER_A2->CCR[4] = d;
    TIMER_A2->CCTL[4] = 0xE0;
    TIMER_A2->CTL = 0x0254;
}