#include <iostream>
using namespace std;

/*
double* initializeArray(int size)
{
	double* ptr = new double(size);
	cout << "Please enter your data: " << endl;
	for (int i = 0; i < size; i++)
	{
		cin>> *(ptr + i);	
	}
	 return ptr;

}
*/
/*
void BinarySearch(double target, const double* begin, const double* end)
{
	int index = -1;
	double* originalbegin = NULL;
	const double* middle = begin + (end - begin)/2; //mid is pointing to the middle index.

	while(begin != end)
	{
		if (target == *middle)
		{
			cout << "The index is: " << middle - originalbegin << endl;
			cout << "Found ";
			break;
		}
		else if (target > *middle)
		{
			begin = middle;
			middle = begin + (end - begin)/2;
		}
		else if (target < *middle)
		{
			end = middle;
			middle = begin + (end - begin)/2;
		}
		cout << "Unable to find ";
	}
	cout << target << endl;
}
*/
int main()
{
	/*
	double* array = NULL;
	double* start = NULL;
	double* end = NULL;
	double target = 0;*/
	int size  = 0;

	cout << "Please enter number of data you want to enter: " << endl;
	cin >> size;
	//array = initializeArray(size);
	//start = &array[0];
	//end = &array[size-1];
	

	return 0;
}

