/****************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 03/05/2021
 * Project: Lab 6 Part 2
 * File: part2main.c
 * Description: This program takes the input from a keypad and prints the last 4
 * numbers pressed when the pound key is pressed. The star symbol does nothing,
 * and the pound key is the enter button. This process can be repeated as many
 * times as needed.
 ****************************************************************************/
#include "msp.h"
#include <stdio.h>

void Keypad_init(void);
int Keypad_Read(void);
void Keypad_Print(int *arr, int t);
void SysTick_delay(int n);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Keypad_init();
    int t=0, pressed=0;           // t is the number of inputs, total 4 numbers
    int arr[]={0,0,0,0};

    printf("Please Enter a 4-digit PIN\n");

    while(1){
        pressed = Keypad_Read();
        if(pressed==12)
            Keypad_Print(arr, t);

        if((pressed!=10)&&(pressed!=12)&&(pressed!=0)){
            if(t>=4){
                arr[0]=arr[1];
                arr[1]=arr[2];
                arr[2]=arr[3];
                arr[3]=pressed;
            }
            else {
                arr[t]=pressed;
                t++;
            }
        }
        SysTick_delay(10);
    }


}
/****| Keypad_init | *****************************************
 * Brief: Initializes all the ports and pins used
 * param: void
 * return: void
 *************************************************************/
void Keypad_init(void){
    //Configure GPIO ROWS: P4 .0 .1 .2 .3 & COL: P4 .4 .5 .6

    //Configure ROWS
    P4SEL1 = 0x00;
    P4SEL0 = 0x00;
    P4DIR = 0x00;
    P4REN = (BIT0 | BIT1 | BIT2 | BIT3);
    P4OUT = (BIT0 | BIT1 | BIT2 | BIT3);

    //Configure COLUMNS
    P4REN &= ~(BIT4 | BIT5 | BIT6);
    P4OUT &= ~(BIT4 | BIT5 | BIT6);
}
/****| Keypad_Read | *****************************************
 * Brief: Determines which button was pressed on the keypad
 * then returns the number code for that key
 * param: void
 * return: int; number code that was pressed
 *************************************************************/
int Keypad_Read(void){
    int col, row, num;
    for (col = 0; col < 3; col++)
    {
        P4DIR = 0x00; //set columns to inputs
        P4DIR |= BIT (4+col); //set column 0 to output
        P4OUT &=~ BIT (4+col); //set column 0 to LOW

        SysTick_delay(10);
        row = P4IN & 0x0F; //read rows
        SysTick_delay(10);

        while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );

        if (row != 0x0F) break; // if one of the input is low, some key is pressed.
    }

    P4DIR = 0x00; // Set Columns to inputs
    if (col == 3)
        return 0;

    if (row == 0x0E) num = col + 1; // key in row 0
    if (row == 0x0D) num = 3 + col +1; // key in row 1
    if (row == 0x0B) num = 6 + col +1; // key in row 2
    if (row == 0x07) num = 9 + col+1; // key in row 3

    return num;
}

/****| Keypad_Print | *****************************************
 * Brief: Takes the number of button presses and the array of
 * the last 4 keys pressed to determine what to print to the console
 * param: int: number array , int: times pressed
 * return: int; number code that was pressed
 *************************************************************/
void Keypad_Print(int *arr, int t){
    int i;
    if(t<4)
        printf("ERROR: too few inputs detected.\n");

    else{
        printf("PIN: ");
        for(i=0;i<4;i++){
            if(arr[i]==11)
                printf("[0]");
            else
                printf("[%d]", arr[i]);
        }
        printf("\nPlease Enter a 4-digit PIN\n");
    }


}
/****| SysTick_delay | *****************************************
 * Brief: Delay using Systick per millisecond
 * param: int n: number of milliseconds to delay
 * return: void
 *************************************************************/
void SysTick_delay(int n){
    int i;
    SysTick->LOAD=(3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;

    for(i=0;i<n;i++){
        while((SysTick->CTRL & BIT(16))==0);
    }

    SysTick->CTRL=0;

}
