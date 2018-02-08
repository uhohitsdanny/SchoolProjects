#include <iostream>
#include <fstream>

//Daniel Navarro
//danielnavarro71@yahoo.com

using namespace std;

int* initializeArray(int nRead);
int binary(int key, const int* start, const int* end);

int main()
{
	int input, searchkey;

	cout << "Number of integers to be read: ";
	cin >> input;
	cout << "Number you want to search for: ";
	cin >> searchkey;

	//get the pointer variables.
	int* ptr = initializeArray(input);
	int* start = &ptr[0];
	int* end = &ptr[input-1];

	int index = binary(searchkey, start, end);
	cout << index << endl;

	//deallocate array memory.
	delete[] ptr;

	return 0;
}
//initialize array with the integers.
int* initializeArray(int nRead)
{
	//Open the numbers file.
	ifstream numbers("number_list.txt");
	if (!numbers.is_open())
	{
		cerr << "File could not be open." << endl;
	}
	else{
		//Create an array from heap.
		int* pointer = new int[nRead];

		//input numbers from file into the array.
		for (int i = 0; i < nRead; i++)
		{
			numbers >> pointer[i];
		}

		//close the file.
		numbers.close();

		//return pointer array.
		return pointer;
	}

}

int binary(int key, const int* start, const int* end)
{
	int index = -1;

	//get the address of the middle element in the array.
	const int* mid = start + (end-start)/2;

	//create new variables to retain original value
	//to use to find the correct index after the number has been found.
	const int* originstart = start;
	const int* originend = end;

	//
	while (start != end){
		if (*mid == key)
		{
			break;
		}
		else if (key < *mid)
		{
			//The number is less than the middle element so the middle
			//is now the end point of your search and the start point is the same
			//because your number is in the lesser half of the array.
			end = mid;

			//Set your new middle value from the lower half.
			mid = start + (end - start) / 2;
		}
		else {
			//Your element is greater than the middle element.  Thus your number is in
			//the greater half of the array.  The middle point is now the starting point.
			//The end point stays the same.
			start = mid;

			//Set the new middle value.
			mid = start + (end - start) / 2;
		}
	}
	//This will subtract the memory address and give you a decimal number which is the index.
	index = mid - originstart;

	return index;
}
