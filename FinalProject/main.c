#include <FuncsLib.h>
#include "msp.h"
#include <stdio.h>
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Setup_Init();
    LCD_init();
    adcsetup();
    Keypad_init();
    PrintMenu(1);
    int n=0, pressed;
    const int pressZeroed=15;
    double DC=0;
    P2OUT |= BIT0;
    P2OUT &=~ BIT1;
    ServoConfig(1999);

    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_EnableIRQ(PORT3_IRQn);
    __enable_interrupt();


    while(1){

        pressed = Keypad_Read();
        switch(n) {                 //if a state needs to be stayed in, make sure that the case stays the same until something is accomplished then exit
        case 0 :                    //Main Menu
            if(pressed==1){
                n=1;
                PrintMenu(2);
                pressed=pressZeroed;
                break;
            }
            else if(pressed==2){
                n=2;
                PrintMenu(3);
                pressed=pressZeroed;
                break;
            }
            else if(pressed==3){
                n=3;
                PrintMenu(4);
                pressed=pressZeroed;
                break;
            }

            break;

        case 1 :                    //Door Menu

            if(pressed==1)          //option 1, open door
            {
                ServoConfig(5499);
                P2OUT &=~ BIT0;
                P2OUT |= BIT1;
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            else if (pressed==2)    //option 2, close door
            {
                ServoConfig(1999);
                P2OUT &=~ BIT1;
                P2OUT |= BIT0;
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }
            else if (pressed==10){  //option 3, exit to main
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;

        case 2 :                        //Motor Menu


            if(pressed==11){
                MotorConfig(0);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            else if((pressed>=1 && pressed <10)){
                DC=Press_Convert(pressed)*37500;
                MotorConfig(DC);        //located in initializer.c
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }
            else if (pressed==10){
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;

        case 3 :                        //RGB Menu

            if(pressed==1){
                n=4;
                PrintMenu(5);
                pressed=pressZeroed;
                break;
            }
            else if(pressed==2){
                n=5;
                PrintMenu(5);
                pressed=pressZeroed;
                break;
            }
            else if(pressed==3){
                n=6;
                PrintMenu(5);
                pressed=pressZeroed;
                break;
            }

            else if(pressed==10){
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;

        case 4 :                        //RGB Red Brightness

            if(pressed==11){
                RGBConfig(0,1);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            else if((pressed>=1 && pressed <10)){
                DC=Press_Convert(pressed);
                RGBConfig(DC,1);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }
            else if (pressed==10){
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;

        case 5 :                        //RGB Green Brightness

            if(pressed==11){
                RGBConfig(0,2);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            else if((pressed>=1 && pressed <10)){
                DC=Press_Convert(pressed);
                RGBConfig(DC,2);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }
            else if (pressed==10){
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;

        case 6 :                        //RGB Blue Brightness

            if(pressed==11){
                RGBConfig(0,3);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            else if((pressed>=1 && pressed <10)){
                DC=Press_Convert(pressed);
                RGBConfig(DC,3);
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }
            else if (pressed==10){
                n=0;
                PrintMenu(1);
                pressed=pressZeroed;
                break;
            }

            break;
        }


        // if the buttons are pressed, toggle LEDs not implemented yet


        ADC14->CTL0 |=1;        //P5.5 from potentiometer, also not fully wired yet
        while(!ADC14->IFGR0);
        int x = ADC14->MEM[5];
        //      printf("%d",x);
        Systick_ms_delay(10);


    }
}
