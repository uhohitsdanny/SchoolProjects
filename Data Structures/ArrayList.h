#include "List.h"	

template < typename T >
class ArrayList : public List < T > 
{
private:
	int size;
	int n;
	T* arr;
public:
	ArrayList() { arr = new T[size]; n = 0; }
	ArrayList(T* array, int size) { 
		arr = array;  
		n = size;
	}
	virtual void Add(const T& element)
	{
		if (size == n)
			Resize();
		arr[size++] = element;
	}
	void Resize(){
		n = n * 2;
		int* temp = new T[n];
		for (int i = 0; i < size - 1; ++i)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		delete[] temp;
	}
	virtual T& Get(Index i)
	{
		if (i >= n || i < 0)
			throw exception("Index out of bounds");
		else
			return arr[i];
	}
	virtual void Set(Index i, const T& val)
	{
		if (i >= n || i < 0)
			throw exception("Index out of bounds.");
		else
			arr[i] = val;
	}
	virtual unsigned int Size()
	{
		return size;
	}
	virtual void Remove(Index i)
	{
		if (i >= n || i < 0)
			throw exception("Index out of bounds.");
		if (int j = i + 1; j < n; ++j)
		{
			arr[j - 1] = arr[j];
		}
		--n;
	}
	virtual void Clear()
	{
		delete[] arr;
		size = 0;
		arr = new T[size];
		n = 20000;
	}
};
