//Daniel Navarro
//danielnavarro71@yahoo.com
//CPSC 254
//Project 3
//Due: March 21, 2016
//Display.cpp
//Displays sorted and unsorted array
//gcc -c -m64 -Wall -o Display.o Display.cpp
#include <iostream>
#include <iomanip>
using namespace std;

extern "C" void displayData(float original[], float datas[], int length);

void displayData(float original[], float datas[], int length)
{
	cout << "Original data set: \n";
	for (int i = 0; i < length; i++)
	{
		cout << " " << fixed << showpoint << setprecision(5) << setw(10) << right << original[i] << endl;
	}
	cout << "Sorted data set: \n";
	for (int i = 0; i < length; i++)
	{
		cout << " " << fixed << showpoint << setprecision(5) << setw(10) << right << datas[i] << endl;
	}
	cout << endl;
}
