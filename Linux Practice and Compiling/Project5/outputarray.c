#include <stdio.h>

void outputarray(int studentscores[][6]);
void outputarray(int studentscores[][6]){
	int i, j;
	for(i = 0; i < 4; i++){
		printf("Student%d: ", (i+1));
		for(j = 0; j<6; j++){
			printf("%d ", studentscores[i][j]);
		}
		printf("\n");
	}
}
