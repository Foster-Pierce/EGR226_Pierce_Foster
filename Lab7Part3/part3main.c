/****************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 03/12/2021
 * Project: Lab 7 Part 3
 * File: part3main.c
 * Description: This program displays one line of characters to the screen
 * and continuously scrolls left one character per .75s until all characters
 * are off the screen, and repeats this forever.
 ****************************************************************************/
#include <LCD_preset_part3.h>
#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    LCD_init();
    write_command(0x80);      //start on line 1 postition 0

    while(1){
        PrintChar();
    }
}
