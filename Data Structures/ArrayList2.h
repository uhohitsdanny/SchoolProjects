#include "List.h"	

template < typename T >
class ArrayList : public List < T > 
{
private:
	int size;
	int n;
	T* arr;
public:
	ArrayList() { arr = new[T]; n = 0; }
	ArrayList(T* array, int index) { 
		arr = array;  
		n = index;
	}
	virtual void Add(const T& element)
	{
		if (size == n)
			Resize();
		arr[size++] = element;
	}
	void Resize(){
		n = n * 2;
		int* temp = new int[n];
		for (int i = 0; i < )
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
			--n;
		}
	}
	virtual void Clear()
	{
		delete[] arr;
		arr = new int[10];
		n = 0;
	}
};
