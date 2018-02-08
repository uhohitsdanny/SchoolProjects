#include <iostream>
#include <math.h>
using namespace std;

extern "C" void computegeometricmean(int sumarray[]);
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
