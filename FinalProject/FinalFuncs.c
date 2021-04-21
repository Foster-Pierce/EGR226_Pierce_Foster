#include <LCD.h>
#include <FuncsLib.h>
#include "msp.h"

const char menu1[4][11]=
{{'M','E','N','U',' ','S','E','L','E','C','T'},
 {'1',')',' ','D','O','O','R',' ',' ',' ',' '},
 {'2',')',' ','M','O','T','O','R',' ',' ',' '},
 {'3',')',' ','L','E','D','s',' ',' ',' ',' '}};

void PulseEnablePin (void){
    P5OUT &=~BIT0;          //pulse low for 10us
    Systick_us_delay(10);
    P5OUT |=BIT0;           //pulse high for 10us
    Systick_us_delay(10);
    P5OUT &=~BIT0;          //pulse low for 10us
    Systick_us_delay(10);
}
void pushNibble (int nibble){
    P2OUT &=~0xF0; // clear P2.4-P2.7
    P2OUT |= (nibble & 0x0F) << 4; // port pins P2.4 - P2.7 wired to D4 - D7
    PulseEnablePin();
}
void pushByte (int byte){
    int nibble;                     //splitting the byte into 4 bit chunks
    nibble = (byte & 0xF0) >> 4;
    pushNibble(nibble);
    nibble = byte & 0x0F;
    pushNibble(nibble);
    Systick_us_delay(100);
}
void write_command (int command){
    pushByte(command);
}
void write_data (int data){
    P5OUT |= BIT2;          //Sets RS
    pushByte(data);
    P5OUT &= ~BIT2;         //clears RS
}

int Keypad_Read(void){
    int col, row, num;
    for (col = 0; col < 3; col++)
    {
        P4DIR = 0x00; //set columns to inputs
        P4DIR |= BIT (4+col); //set column 0 to output
        P4OUT &=~ BIT (4+col); //set column 0 to LOW

        Systick_ms_delay(10);
        row = P4IN & 0x0F; //read rows
        Systick_ms_delay(10);

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
void PrintMenu1(int c){
    int i;
    write_command(6); //entry mode
    for(i=0;i<11;i++)
        write_data(menu1[c][i]);

}
void PrintMainMenu(void){
    write_command(0x82);        //begin on line 1
    PrintMenu1(0);               //print line one characters
    write_command(0xC3);        //begin line 2, etc.
    PrintMenu1(1);
    write_command(0x93);
    PrintMenu1(2);
    write_command(0xD3);
    PrintMenu1(3);
    write_command(0xDA);
}

double Press_Convert(int n){
    if((n<=9)&&(n>0)){          //assigns the key pressed to it's respected duty cycle value
        double DC=(double)n/10;
        return DC;
    }
    else if(n==10)
        return 1;
    else if(n==11)
        return 0;
    else if(n==12)
        return 0;

    return 0;
}

void MotorSpeed(double x){
    int duty=37500*x;
    MotorConfig(duty);
}

void debouncer(void){
    // initialize TimerA1.1 with interrupts for 10s
    TIMER_A1->CCR[0] = 30001;
    TIMER_A1->CCR[1] = 30000;
    TIMER_A1->CCTL[1] = 0x10;
    TIMER_A1->CTL = 0x0254;

}
void TA1_N_IRQHandler(void){                //modify to fit the 5 buttons
    //if red button was pressed
    if((P3IN & BIT5) == 0){

    }
    //if green button was pressed
    else if((P3IN & BIT6) == 0){

    }
    //if blue button was pressed
    else if((P3IN & BIT7) == 0){

    }
    //if white button was pressed
    else if((P3IN & BIT2) == 0){

    }
    //if black button was pressed
    else if((P3IN & BIT3) == 0){

    }
    TIMER_A1->CTL=0;        //disables TimerA1.1 and interrupt flag
    TIMER_A1->CCTL[1]=0;
}

void PORT3_IRQHandler (void){   // port 3 service routine (buttons)
    debouncer();            //timer enabled with interrupts begin running for 10ms delay
    P3IFG=0;
}