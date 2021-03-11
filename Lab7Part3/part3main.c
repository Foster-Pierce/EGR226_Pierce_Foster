#include "msp.h"
#include "LCD_preset.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    LCD_init();
    write_command(0x80);      //start on line 1 postition 0

    while(1){
        PrintChar();
    }
}
