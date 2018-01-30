// Assignment 1: Alternating disks problem, left-to-right algorithm   
// SangYong Jin, Daniel Navarro, Shelley Chiang Pham
// Given 2n alternating disks (dark, light) the program reads the number of single color disks 
// (light or dark), arranges the disks in the correct order and outputs the number of swaps 
// INPUT: a positive integer n and a list of 2n disks of alternating colors dark-light, starting with dark 
// OUTPUT: a list of 2n disks, the first n disks are light, the next n disks are dark,  
// and an integer m representing the number of moves to move the dark ones after the light ones  

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
void print_disks(int n, char *disks){

	for (int i = 0; i < n; i++)
	
	cout << disks[i];
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
	cout << "The alternating disks problem: left-to-right algorithm" << endl;
	cout << "Enter the number of single color disks (light or dark)" << endl;
	// read the number of disks 
	cin >> n;
	int x = 2 * n;
	// allocate space for the disks                                                                                                                                                                        
	disks = new char[2 * n];
	// set the initial configurations for the disks to alternate 
	for (i = 0; i < (x/2); i++) {
		disks[2 * i] = 'd';
		disks[2 * i + 1] = 'l';
	}
	cout << endl;
	
	// print the initial configuration of the list of disks  
	cout << "Initial configuration" << endl;
	print_disks(x, disks);
	// PART OF CODE MISSING
	// loop to push light one before the darks ones 
	for (k = 0; k < x; k++) {
		// YOU NEED TO COMPLETE THIS PART OF CODE FOR GOING LEFT TO RIGHT
		for (int y = 0; y < x-1; y++){
			if (disks[y] == 'd'){
				if (disks[y + 1] != 'd'){
					swap(disks[y], disks[y + 1]);
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
