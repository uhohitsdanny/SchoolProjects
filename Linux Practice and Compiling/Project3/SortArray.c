
#include <stdio.h>

void sortArray(float datas[], int length);
void sortArray(float datas[], int length)
{
  float temp = 0.0;
  int begin = 0;
  int save_i = 0;
  int i;

  while(begin < length-1)
  {
      float min = datas[begin];
      for(i = begin + 1; i < length; i++)
      {
        if(min > datas[i])
        { 
          min = datas[i];
          save_i = i;
        }
      }
      temp = datas[begin];
      datas[begin] = datas[save_i];
      datas[save_i] = temp;
    begin++;
  }
}
