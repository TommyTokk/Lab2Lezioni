#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
 
// main function to find the execution time of a C program
int main()
{
    // to store the execution time of code
    double time_spent = 0.0;
 
    clock_t begin = clock();
 
    int x = 1;
    while(x != 1000000000) x++;
 
    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf(" %d \n", x);
 
    return 0;
}