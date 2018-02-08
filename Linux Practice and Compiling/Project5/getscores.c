#include <stdio.h>
void getscores(int scores[][6]);
void getscores(int scores[][6]){
					
	FILE *myfile;
	myfile = fopen("scores10students.txt", "r");
	int i;
	int j;
	
	if (myfile == NULL)
    {
        printf("Error Reading File\n");
    }
    
	for(i = 0; i < 4; i++){
		for(j = 0; j <6; j++){
			fscanf(myfile, "%d", &scores[i][j]);
		}
	}
	fclose(myfile);
}
