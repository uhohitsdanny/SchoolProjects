float computeMean(float data[], int length)
{
	int i;
	float sum = 0;
  for (i = 0; i < length; i++)
  {
    sum += data[i];
  }
  return sum/length;
}
