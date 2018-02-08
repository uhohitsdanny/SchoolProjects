#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

extern "C" void getscores(int scores[][6]);
void computesum(int studentscores[][6], int sumarray[]);
void computegeometricmean(int sumarray[]);
extern "C" void outputarray(int studentscores[][6]);
//extern "C" outputsum(int sumarray[]);

int main(){
	int studentscores[4][6] = {};
	int sumscores[4] = {};	
	getscores(studentscores);
	computesum(studentscores, sumscores);
	computegeometricmean(sumscores);	
	
	return -1;
}
	
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
void computegeometricmean(int sumarray[]){
	long double product = 1;
	double geometricmean = 0;
	double squarecount = 0;
	for(int i = 0; i<4; i++)
	{
		product *= sumarray[i];
		squarecount++;
	}
	geometricmean = pow(product,(1/squarecount));
	cout << "Geometric Mean: " << geometricmean << endl;
}


