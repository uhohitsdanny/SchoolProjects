#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void getscores(int scores[][6]);
void computesum(int studentscores[][6], int sumarray[]);
void computegeometricmean(int sumarray[]);
void outputarray(int studentscores[][6]);
void outputsum(int sumarray[]);

int main(int argc, char *argv[]){
	int studentscores[4][6] = {};
	int sumscores[4] = {};	
	getscores(studentscores);
	outputarray(studentscores);
	computesum(studentscores, sumscores);
	outputsum(sumscores);	
	computegeometricmean(sumscores);
	
	return 0;
}
	



