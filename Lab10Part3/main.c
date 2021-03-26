#include <FuncLibPart3.h>
#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    LCD_init();
    adcsetup();
    write_command(0x85);        //begin on line 1
    PrintChar();

    SysTick_Init_interrupt();
    __enable_interrupt();
    while(1){
      int  x= getflag(1);
        if(x==1){
        double x =0, Celsius=0, volt=0;

            ADC14->CTL0 |=1;
            while(!ADC14->IFGR0);

            x = ADC14->MEM[5];
            volt = x*0.0002;
            Celsius = (volt*1000-500)/10;

            printf("Temperature in Celcius:\t%.1f\n", Celsius);

            write_command(0xC7);
            UpdateTemp(Celsius);
            Systick_ms_delay(500);

        }
        SysTick_Init_interrupt();
    }
}