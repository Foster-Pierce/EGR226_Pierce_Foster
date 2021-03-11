#include "msp.h"
#include "LCD_preset.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    LCD_init();
    write_command(0x85);
    PrintChar(0);
    write_command(0xC5);
    PrintChar(1);
    write_command(0x96);
    PrintChar(2);
    write_command(0xD6);
    PrintChar(3);
    write_command(0xD9);
    while(1){
        ;
    }
}
