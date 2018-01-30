// Assignment 1: Alternating disks problem, left-to-right algorithm                                                                                                                              
//  SangYong Jin, Daniel Navarro, Shelley Chiang Pham
// Given 2n alternating disks (dark, light)  the program reads the number of single color disks 
// (light or dark), arranges the disks in the correct order and outputs the number of swaps 
// INPUT: a positive integer n and a list of 2n disks of alternating colors dark-light, starting with dark 
// OUTPUT: a list of 2n disks, the first n disks are light, the next n disks are dark, 
// and an integer m representing the number of moves to move the dark ones after the light ones

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
void print_disks(int n, char *disks){
	for (int i = 0; i < n; i++){

		cout << disks[i];
	}

}
// YOU NEED TO IMPLEMENT THIS FUNCTION
// function to print the list of disks, given the number of single color disks and the actual list
// n represents the number of single color disks
// disks represents the list of disks (index 0 being the first disk) where 
// 0 = a light color disks                                                                                                      
// 1 = a dark color disks 
int main() {
	int n, m=0, k, i;
	char *disks;
	// display the header 
	cout << endl << "CPSC 335-x - Programming Assignment #1" << endl;
	cout << "The alternating disks problem: lawnmower algorithm" << endl;
	cout << "Enter the number of single color disks (light or dark)" << endl;
	// read the number of disks 
	cin >> n;
	// allocate space for the disks
	disks = new char[2 * n];
	int x = n * 2;
	// set the initial configurations for the disks to alternate 
	for (i = 0; i < (x/2); i++) {
		disks[2 * i] = 'd';
		disks[2 * i + 1] = 'l';
	}
	// print the initial configuration of the list of disks
	cout << "Initial configuration" << endl;
	print_disks(x, disks);
	// PART OF CODE MISSING
	// loop to push light one before darks ones 
	for (k = 0; k < n / 2 + 1; k++) {
		// DEVELOP ONE FOR LOOP FOR GOING LEFT TO RIGHT
		// DEVELOP ANOTHER FOR LOOP FOR GOING RIGHT TO LEFT
		for (int i = 0; i < (x-1); i++){
			if (disks[i] == 'd'){
				if (disks[i + 1] != 'd'){
					swap(disks[i], disks[i + 1]);
					m++;
				}
			}
		}
		
		for (int i = (x-1); i > 0; i--){
			if (disks[i-1] == 'd'){
				if (disks[i] != 'd'){
					swap(disks[i], disks[i-1]);
					m++;
				}
			}
		}
	
	}
	cout << endl;
	// after shuffling them
	cout << "After moving darker ones to the right" << endl;
	print_disks(x, disks);
	cout << endl;
	// print the total number of moves
	cout << "Number of swaps is " << m << endl;
	// de-allocate the dynamic memory space
	delete[] disks;
	return EXIT_SUCCESS;
}
