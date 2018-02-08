//Daniel Navarro
//danielnavarro71@yahoo.com
//CPSC 254
//Project 3
//Due: March 21, 2016
//Get_Data.c
//Gets user input.
//gcc -c -m64 -Wall -o Get_Data.o Get_Data.c

#include <stdio.h>

void Get_Data(float original[], float datas[], int* length);
void Get_Data(float original[], float datas[], int* length)
{
    int count = 0;
    printf("Enter data and Ctrl + D when you're done(Ctrl + Z for Windows): \n");
    
    while (scanf("%f", &datas[count]) != EOF)
    {
		original[count] = datas[count];
        count++;
    }
	*length = count;
}
