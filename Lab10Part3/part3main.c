#include <FuncLibPart3.h>
#include "msp.h"
volatile int flag=0;
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    LCD_init();
    adcsetup();
    write_command(0x85);        //begin on line 1
    PrintChar();

    SysTick_Init_interrupt();
    __enable_interrupt();
    double x =0, Celsius=0, volt=0;

    while(1){
        if(flag){

            ADC14->CTL0 |=1;
            while(!ADC14->IFGR0);

            x = ADC14->MEM[5];
            volt = x*0.0002;
            Celsius = (volt*1000-500)/10;

            printf("Temperature in Celsius:\t%.1f\n", Celsius);

            write_command(0xC7);
            UpdateTemp(Celsius);
            flag=0;
            SysTick_Init_interrupt();
        }
    }
}

void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(1500000-1);      //second delay between displaying numbers
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}

void SysTick_Handler (void) {
    flag=1;
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
