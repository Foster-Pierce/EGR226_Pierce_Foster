#include "msp.h"
#include "LCD_preset.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    LCD_init();
    PrintChar(0);
    PrintChar(1);
    PrintChar(2);
    PrintChar(3);
    while(1){
        ;
    }
}



  //  write_data(0x20); //space
