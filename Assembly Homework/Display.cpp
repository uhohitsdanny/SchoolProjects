#include <iostream>
#include <iomanip>
using namespace std;

extern "C" void displayData(float original[], float datas[], int length);

void displayData(float original[], float datas[], int length)
{
	cout << "Original data set: ";
	for (int i = 0; i < length; i++)
	{
		cout << " " << original[i] << endl;
	}
	cout << "Sorted data set: ";
	for (int i = 0; i < length; i++)
	{
		cout << " " << fixed << showpoint << setprecision(5) << setw(10) << datas[i] << endl;
	}
	cout << endl;
}
