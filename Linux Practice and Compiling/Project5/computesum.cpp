#include <iostream>
using namespace std;

extern "C" void computesum(int studentscores[][6], int sumarray[]);
void computesum(int studentscores[][6], int sumarray[]){
	
	for(int i = 0; i<4; i++)
	{
		int sum = 0;
		for(int j = 0; j<6; j++)
		{
			sum += studentscores[i][j];
		}
		sumarray[i] = sum;
	}
}
