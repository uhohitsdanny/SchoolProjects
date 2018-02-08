#include <iostream>
using namespace std;

extern "C" float Compute_Median(float datas[], int length);

float Compute_Median(float datas[], int length)
{
  int middle = (length -1)/2;
  
  if (length%2 == 0)
      return (datas[middle] + datas[middle + 1])/ 2;
  else
      return datas[middle];
}