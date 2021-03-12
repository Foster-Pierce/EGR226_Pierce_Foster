/****************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 03/12/2021
 * Project: Lab 7 Part 2
 * File: part2main.c
 * Description: This program displays four lines of information to the LCD.
 * The first 2 lines are the first and last names of the user, and the next
 * line is the class name, and the last line is the class number. This
 * information stays on the screen with no other effects.
 ****************************************************************************/
#include <LCD_preset_part2.h>
#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    LCD_init();                 //initialize the LCD
    write_command(0x85);        //begin on line 1
    PrintChar(0);               //print line one characters
    write_command(0xC5);        //begin line 2, etc.
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
