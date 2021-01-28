#include "stats_lib.h"
#include <math.h>

float maximum(float nums[],int n){
float x=nums[0];
int i;
for(i=0;i<n;i++){
    if(nums[i]>x)
        x=nums[i];
}
printf("1. Maximum: %.0f\n", x);
return 0;
}

float minimum(float nums[],int n){
float x=nums[0];
int i;
for(i=0;i<n;i++){
    if(nums[i]<x)
        x=nums[i];
}
printf("2. Minimum: %.0f\n", x);
return 0;
}

float mean(float nums[],int n){
float avg,sum;
int i;
for (i=0;i<n;i++) {
        sum += nums[i];
    }
    avg = sum / n;
    printf("3. Mean: %.2f\n", avg);

return 0;
}

float median(float nums[],int n){
int i=0 , j=0 , temp=0;
float median=0;
// uses a temp variable to sort the data
for(i=0 ; i<n ; i++)
{
for(j=0 ; j<n-1 ; j++)
{
    if(nums[j]>nums[j+1])
    {
    temp = nums[j];
    nums[j] = nums[j+1];
    nums[j+1] = temp;
    }
}
}
// when n is even
if(n%2 == 0)
    median = (nums[(n-1)/2] + nums[n/2])/2.0;
// when n is odd
else
    median = nums[n/2];
printf("4. Median: %.0f\n", median);
return 0;
}

float variance(float nums[],int n){
int i;
float Mean, Variance, SD, Sum=0, Differ, Varsum=0;

for (i=0;i<n;i++) {
    Sum += nums[i];
    }
    Mean = Sum / n;
// finds the sum portion of the variance equation
for(i=0;i<n; i++)
{
     Differ = nums[i] - Mean;
     Varsum += pow(Differ,2);
}
Variance = Varsum / (n-1);
printf("5. Variance: %.2f\n", Variance);

return 0;
}

float standard_deviation(float nums[],int n){
int i;
float Mean, Variance, SD, Sum=0, Differ, Varsum=0;

for (i=0;i<n;i++) {
    Sum += nums[i];
    }
    Mean = Sum / n;
// finds the sum portion of the variance equation
for(i=0;i<n; i++)
{
     Differ = nums[i] - Mean;
     Varsum += pow(Differ,2);
}
Variance = Varsum / (n-1);
SD = sqrt(Variance);

printf("6. Standard deviation: %.2f\n", SD);
return 0;
}
