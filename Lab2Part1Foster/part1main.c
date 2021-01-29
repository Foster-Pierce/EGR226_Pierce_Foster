/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 02/05/2021
* Project: Lab 2 Part 1
* File: part1main.c
* Description:
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxstring 1000
#define strings 10
#define colorcode 12

void prompt(void);
void calcResistorColors(int);
void getColorBands(char*,char*,char*,char*);
void calcResistance(char,char,char,char);

int main()
{
int userResistance, decision=1;


//add prompt choice (1) or (2)

while (decision!=0){
        prompt();

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
    return 0;
}

/****| prompt | *****************************************
* Brief: Displays the prompt for the program
* param: void
* return: N/A
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
* return: N/A
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

void getColorBands(char*,char*,char*,char*){
char in1,in2,in3,in4;

printf("Input Color Band 1 Character:\n");
char*=scanf("%c", in1&);
printf("Input Color Band 2 Character:\n");
char*=scanf("%c", in2&);
printf("Input Color Band 3 Character:\n");
char*scanf("%c", in3&);
printf("Input Color Band 4 Character:\n");
char*scanf("%c", in4&);

}



void calcResistance(char,char,char,char){
int count = 0, i, base =1, multiplier, first, second, third, count2, resistance;
float tolerance;
char arr[maxstring][colorcode] =
{
    'k',
    'n',
    'r',
    'o',
    'y',
    'g',
    'b',
    'v',
    'e',
    'w',
    'd',
    's'
};
char multiply[maxstring][colorcode] =
{
    'k',
    'n',
    'r',
    'o',
    'y',
    'g',
    'b',
    'v',
    'e',
    'w',
    'd',
    's'
};
char toleranced[maxstring][colorcode] =
{
    'k',
    'n',
    'r',
    'o',
    'y',
    'g',
    'b',
    'v',
    'e',
    'w',
    'd',
    's'
};
//check if input char is equal to an array char then assign number by concantenating the first two, multiplying that by the multiplier, then adding %%
for(i=0;i<12;i++){
    if(in1 == arr[i]){

    }
}




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
printf("Your output is: %d +/- %d%\n", resistance, tolerance);
}
