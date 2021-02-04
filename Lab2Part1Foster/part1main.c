/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 02/05/2021
* Project: Lab 2 Part 1
* File: part1main.c
* Description: This code takes either a color code or resistance number, and converts
* it to the opposite, printing it on screen.
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define maxstring 1000
#define strings 10
#define colorcode 12

void prompt(void);
void calcResistorColors(int);
void getColorBands(char*,char*,char*,char*);
void calcResistance(char,char,char,char);

int main()
{
int userResistance, decision=1,choice;
char in1,in2,in3,in4;

while (decision!=0){
        prompt();
        scanf("%d", &choice);

    if (choice==2){
while ((getchar()) != '\n');
getColorBands(&in1,&in2,&in3,&in4);
printf("%c, %c, %c, %c\n", in1,in2,in3,in4);

calcResistance(in1,in2,in3,in4);

printf("to try again press '1' or '0' to quit: \n");
scanf("%d",&decision);
}


else {
printf("Please enter integer resistance number\n");
        // error checking for non integer
if(scanf("%d", &userResistance) != 1) {
    printf("failure to read valid input, try again\n");
    while ((getchar()) != '\n');
}
else {
        // error checking for invalid integer
while (userResistance <0 || userResistance >99000000){

    printf("failure to read valid input, try again\n");
    prompt();
    scanf("%d", &userResistance);
}
calcResistorColors(userResistance);
printf("to try again press '1' or '0' to quit: \n");
scanf("%d",&decision);
}
}
}
    return 0;
}

/****| prompt | *****************************************
* Brief: Displays the prompt for the program
* param: void
* return: prompt to the terminal
*************************************************************/
void prompt(void) {

printf("--------------------Resistor Codes---------------------\n");
 printf("|Character| Color  | Band 1 & 2 |   Band 3   |  Band 4 |\n");
 printf("|    K    | Black  | 0          |*1          |+/- 1%%   |\n");
 printf("|    N    | Brown  | 1          |*10         |+/- 2%%   |\n");
 printf("|    R    | Red    | 2          |*100        |         |\n");
 printf("|    O    | Orange | 3          |*1,000      |         |\n");
 printf("|    Y    | Yellow | 4          |*10,000     |         |\n");
 printf("|    G    | Green  | 5          |*100,000    |+/- 0.5%% |\n");
 printf("|    B    | Blue   | 6          |*1,000,000  |+/- 0.25%%|\n");
 printf("|    V    | Violet | 7          |*10,000,000 |+/- 0.1%% |\n");
 printf("|    E    | Grey   | 8          |            |+/- 0.05%%|\n");
 printf("|    W    | White  | 9          |            |         |\n");
 printf("|    D    | Gold   |            |            |+/- 5%%   |\n");
 printf("|    S    | Silver |            |            |+/- 10%%  |\n");
 printf("-------------------------------------------------------\n\n");
 printf("Convert to color code? (1)\nConvert from color code? (2)\n");
}

/****| calcResistorColors | *****************************************
* Brief: Takes the integer value from the input and
* assigns the proper color code and prints it to the screen
* param: int userResistance: resistance number inputted
* return: all 3 resistor band colors in a printed statement
*************************************************************/
void calcResistorColors(userResistance) {
int count = 0, i, base =1, multiplier, first = userResistance, second = userResistance, count2;
char arr[maxstring][strings] =
{
    "black",
    "brown",
    "red",
    "orange",
    "yellow",
    "green",
    "blue",
    "violet",
    "grey",
    "white"
};

while (userResistance >= 100){
userResistance= userResistance/10;
count++;
}

if(count>0){
for (i=0;i<count;i++)
multiplier = base*10;
}
while(first >= 10){
    first = first/10;
}
while(second >= 10){
    second = (second/pow(10,count));
    second = second %10;
}
printf("Your output is: %s-%s-%s\n", arr[first],arr[second],arr[count]);
}
/****| getColorBands | *****************************************
* Brief: Takes char input from the user that they want to convert
* to a resistance number as a pointer to be used later
* param: char* in1, in2, in3, in4 : pointers to the char inputs
* return: The 4 char inputs from the user to use in main()
*************************************************************/
void getColorBands(char*in1,char*in2,char*in3,char*in4){
char inp1,inp2,inp3,inp4;
int exit=1;
while (exit!=0){

printf("Input Color Band 1 Character:\n");
scanf("%c", &inp1);
*in1 = inp1;
while ((getchar()) != '\n');
printf("Input Color Band 2 Character:\n");
scanf("%c", &inp2);
*in2 = inp2;
while ((getchar()) != '\n');
printf("Input Color Band 3 Character:\n");
scanf("%c", &inp3);
*in3 = inp3;
while ((getchar()) != '\n');
printf("Input Color Band 4 Character:\n");
scanf("%c", &inp4);
*in4 = inp4;
while ((getchar()) != '\n');
exit = 0;
}
return 0;
}
/****| calcResistance | *****************************************
* Brief: Takes char input from the user and converts them into
* the resistance value and tolerance
* param: char in1, in2, in3, in4 : char inputs from the user
* return: value of the resistance
*************************************************************/
void calcResistance(char in1,char in2,char in3,char in4){
int count = 0, i, base =1, multiplier, first, second, third, count2, resistance, exit=0;
float tolerance;
char s1[20];
char s2[20];
printf("Your output is:\n");
// going through all cases (inputs) to see if there are any errors, if any are found it displays which one was invalid and ask for retry
while(exit!=1){
   switch(in1) {
         case 'k' :
             in1 = (int)0;
             break;
         case 'n' :
             in1 = (int)1;
             break;
         case 'r' :
             in1 = (int)2;
             break;
         case 'o' :
             in1 = (int)3;
             break;
         case 'y' :
             in1 = (int)4;
             break;
         case 'g' :
             in1 = (int)5;
             break;
         case 'b' :
             in1 = (int)6;
             break;
         case 'v' :
             in1 = (int)7;
             break;
         case 'e' :
             in1 = (int)8;
             break;
         case 'w' :
             in1 = (int)9;
             break;
      default :
         printf("Invalid\n");
         exit=1;
   }
   switch(in2) {
         case 'k' :
             in2 = (int)0;
             break;
         case 'n' :
             in2 = (int)1;
             break;
         case 'r' :
             in2 = (int)2;
             break;
         case 'o' :
             in2 = (int)3;
             break;
         case 'y' :
             in2 = (int)4;
             break;
         case 'g' :
             in2 = (int)5;
             break;
         case 'b' :
             in2 = (int)6;
             break;
         case 'v' :
             in2 = (int)7;
             break;
         case 'e' :
             in2 = (int)8;
             break;
         case 'w' :
             in2 = (int)9;
             break;
      default :
         printf("Invalid\n");
         exit=1;
   }
sprintf(s1, "%d", in1);
sprintf(s2, "%d", in2);
strcat(s1, s2);
int conc = atoi(s1);

   switch(in3) {
         case 'k' :
         printf("%d ", conc);
         break;
         case 'n' :
         printf("%d ", conc*10);
         break;
         case 'r' :
         printf("%d ", conc*100);
         break;
         case 'o' :
         printf("%d ", conc*1000);
         break;
         case 'y' :
         printf("%d ", conc*10000);
         break;
         case 'g' :
         printf("%d ", conc*100000);
         break;
         case 'b' :
         printf("%d ", conc*1000000);
         break;
         case 'v' :
         printf("%d ", conc*10000000);
         break;
         case 'd' :
         printf("%d ", conc*0.1);
         break;
         case 's' :
         printf("%d ", conc*0.01);
         break;
      default :
         printf("Invalid\n");
         exit=1;
   }
   switch(in4) {
         case 'k' :
         printf("+/- 1%%\n" );
         break;
         case 'n' :
         printf("+/- 2%%\n" );
         break;
         case 'g' :
         printf("+/- 0.5%%\n" );
         break;
         case 'b' :
         printf("+/- 0.25%%\n" );
         break;
         case 'v' :
         printf("+/- 0.1%%\n" );
         break;
         case 'e' :
         printf("+/- 0.05%%\n" );
         break;
         case 'd' :
         printf("+/- 5%%\n" );
         break;
         case 's' :
         printf("+/- 10%%\n" );
         break;
      default :
         printf("Invalid\n");
         exit=1;
   }
   exit = 1;
}
}

