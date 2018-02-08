#include <stdio.h>
void outputsum(int sumarray[]);
void outputsum(int sumarray[]){
	int i;
	for(i = 0; i< 4; i++){
		printf("Student%d sum: ", (i+1));
		printf("%d\n", sumarray[i]);
	}
}
