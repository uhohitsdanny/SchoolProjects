
#include <stdio.h>

float computeMean(float datas[], int length);
float computeMean(float datas[], int length)
{
	int i;
	float sum = 0;
  for (i = 0; i < length; i++)
  {
    sum += datas[i];
  }
  return sum/length;
}
