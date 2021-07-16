#include <iostream>
using namespace std;

extern "C" float Harmonic_Mean(float datas[], int length);

float Harmonic_Mean(float datas[], int length)
{
  float sum = 0.0;
  for (int i = 0; i < length; i++)
  {
    sum += 1/datas[i];
  }
  return length/sum;
}
