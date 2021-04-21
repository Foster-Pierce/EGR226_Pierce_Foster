#include <LCD.h>
#include <FuncsLib.h>
#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Setup_Init();
    LCD_init();
    adcsetup();
    Keypad_init();
    PrintMainMenu();
  //  int n=0;


    NVIC_EnableIRQ(TA1_N_IRQn);
    NVIC_EnableIRQ(PORT3_IRQn);
    __enable_interrupt();
    while(1){
/*
        switch(n) {
        case 0 :

            break;
        case 1 :

            break;
        }
        */
    }
}

    //ADC
    /*
     * ADC14->CTL0 |=1;
            while(!ADC14->IFGR0);

            x = ADC14->MEM[5];
            volt = x*0.0002;
            Celsius = (volt*1000-500)/10;
     */