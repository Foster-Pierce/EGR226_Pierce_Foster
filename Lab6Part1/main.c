#include "msp.h"
#include <stdio.h>

void Keypad_init(void);
int Keypad_Read(void);
void Keypad_Print(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}
void Keypad_init(void){



}

int Keypad_Read(void){
    int col, row;
    for (col = 0; col < 3; col++ )
    {
        P4->DIR = 0x00; // Set Columns to inputs
        P4->DIR |= BIT ( 4+COL ); // Set column 3 to output
        P4->OUT &=~ BIT ( 4+COL ); // Set column 3 to LOW

        SysTick_delay (10); // Delay the while loop
        row = P4->IN & 0x0F; // read all rows

        while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );

        if (row != 0x0F) break; // if one of the input is low, some key is pressed.
    }
    P2->DIR = 0x00; // Set Columns to inputs
    if ( col == 3)
        return 0;

    if (row == 0x0E) num = col + 1; // key in row 0
    if (row == 0x0D) num = 3 + col +1; // key in row 1
    if (row == 0x0B) num = 6 + col +1; // key in row 2
    if (row == 0x07) num = 9 + col+1; // key in row 3

    return 1;
}

void Keypad_Print(void){


}
