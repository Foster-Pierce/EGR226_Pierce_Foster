/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 01/29/2021
* Project: Lab 1 Part 1
* File: part1main.c
* Description: This program takes the integer input of a resistance and then
* outputs the color code of this resistance to the screen.
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxstring 1000
#define strings 10

void prompt(void);
void calcResistorColors(int);


int main()
{
int userResistance, decision=1;

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

 printf("---------------Resistor Codes---------------\n");
 printf("|Character| Color | Band 1 & 2 | Band 3 |\n");
 printf("| K | Black | 0 |*1 |\n");
 printf("| N | Brown | 1 |*10 |\n");
 printf("| R | Red | 2 |*100 |\n");
 printf("| O | Orange | 3 |*1,000 |\n");
 printf("| Y | Yellow | 4 |*10,000 |\n");
 printf("| G | Green | 5 |*100,000 |\n");
 printf("| B | Blue | 6 |*1,000,000 |\n");
 printf("| V | Violet | 7 |*10,000,000|\n");
 printf("| E | Grey | 8 | |\n");
 printf("| W | White | 9 | |\n");
 printf("| D | Gold | | |\n");
 printf("| S | Silver | | |\n");
 printf("---------------------------------------------\n\n");

 printf("What resistance to be color coded?\n");
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
