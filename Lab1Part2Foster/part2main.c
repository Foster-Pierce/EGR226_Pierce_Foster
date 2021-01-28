/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 01/29/2021
* Project: Lab 1 Part 2
* File: part2main.c
* Description: This program finds the min, max, mean, median, variance, and standard
* deviation of a data file and prints them to the screen
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stats_lib.h"

#define MAX 1000
int main(){
    FILE *fpin;

    float nums[MAX];
    int n, i, counter=0;
    fpin = fopen("data.txt", "r");

if (fpin == NULL) {
    printf("The file doesn't exist in the desired location.\n");
    exit(-1);
}
    //scanning in numbers from file
for (i=0;fscanf(fpin, "%f", &nums[i]) != EOF;i++)
{
    counter++;
    n = counter;
}
    fclose(fpin);

    maximum(nums,n);
    minimum(nums,n);
    mean(nums,n);
    median(nums,n);
    variance(nums,n);
    standard_deviation(nums,n);

    return 0;
}


