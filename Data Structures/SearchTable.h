#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using a search table
 * T1 is the type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class SearchTable : public Map<T1, T2>
{
public:	 
	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	virtual void Erase(const T1& k)
	{ 	//Attempt to erase the element
        int index = BinarySearch(k);
        if (index < 0)
            throw Map<T1,T2>::ELE_DNE;
        for (int j = index + 1; j < n; ++j)
            arr[j-1] = arr[j];
        --n;
	}
	 
	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	virtual T2& Find(const T1& k) const
	{	//Attempt to find the element
        int index = BinarySearch(k);
        if (index < 0)
            throw Map<T1,T2>::ELE_DNE;
        return arr[index].value;
	}
	
	/**
	 * Overloaded assignment operator. Perform
	 * a deep copy of the parameter.
	 * @param rhs The object to copy
	 * @return A reference to the calling object
	 */
	SearchTable& operator=(const SearchTable& rhs)
	{
        if (this == &rhs)
            return this;
        n = 0;
        max = rhs.max;
        arr = new KeyValue[max];
        
        for (int i = 0; i < rhs.Size(); ++i)
            Put(rhs.arr[i].key, rhs.arr[i].value);
	}
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v)
	{	//Check if resize is necessary
        if (n >= max)
            ResizeArr(max * 2);
        KeyValue kv = KeyValue(k, v);
        arr[n++] = kv;
        Sort();
	}

	//Default constructor
	SearchTable()
	{
        n = 0;
        max = DEF_CAPC;
        arr = new KeyValue[max];
	}

	//Copy constructor
	SearchTable(const SearchTable& st)
	{
        if (this == st)
            return;
        n = 0;
        max = st.max;
        arr = new KeyValue[max];
        
        for (int i = 0; i < st.Size(); ++i)
            Put(st.arr[i].key, st.arr[i].value);
	}
	
	/**
	* Takes as argument an array of keys and
	* and array of values. Copies of the key value pairs
	* are internally and then sorted. Both arrays
	* must have the same size
	* @param keys The array of keys
	* @param vals The array of values
	* @param numEle The number of key-value pairs
	*/
	SearchTable(const T1* keys, const T2* vals, unsigned int numEle)
	{
        n = 0;
        max = numEle;
        for (int i = 0; i < numEle; ++i)
            Put(keys[i], vals[i]);
	}

	//Virtual destructor
	virtual ~SearchTable()
	{
		delete [] arr;
	}

	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	virtual unsigned int Size() const
	{	
        return n;
	}
	
private:
	//Default capacity
	const static int DEF_CAPC = 10;

	/**
	* Private class for specifying the (key, value)
	* pair. The template <typename T1, T2> is not needed
	* here as it is implied from the top level template
	* declaration on ListMap itself. The implied template
	* parameters are T1 and T2.
	*/
	class KeyValue
	{	//Make the data members public for easy access
	public:
		T1 key;
		T2 value;
        
        KeyValue() {
        }
        
        KeyValue(const T1& k, const T2& v) {
            key = k;
            value = v;
        }
	};
	
	/**
	 * Performs a binary search on the sorted array
	 * @param k The key to search for
	 * @return The index of the key if found; -1 if not found
	 */
	int BinarySearch(const T1& k) const
	{
        int s = 0;
        int e = n - 1;
        int m = -1;
        while (s <= e) {
            m = s + (e - s) / 2;
            if (k == arr[m].key)
                return m;
            else if (k > arr[m].key)
                s = m + 1;
            else
                e = m - 1;
        }
        return - 1;
	}
	
	/**
	 * Resize the list's array
	 * @param The new size of the array
	 */
	void ResizeArr(unsigned int cap)
	{
        max = cap;
        KeyValue* tmp = new KeyValue[cap];
        for (unsigned int i = 0; i < n; ++i)
            tmp[i] = arr[i];
        delete[] arr;
        arr = tmp;
	}

    void Swap(KeyValue& kv1, KeyValue& kv2)
    {
        KeyValue tmp = kv1;
        kv1 = kv2;
        kv2 = tmp;
    }
    
    void SelectionSort(KeyValue* arr, int n) {
        int minIndex;
        for (int j = 0; j < n - 1; ++j) {
            T1 min = arr[j].key;
            minIndex = j;
            for (int i = j + 1; i < n; ++i)
                if (arr[i].key < min) {
                    min = arr[i].key;
                    minIndex = i;
                    
                }
            Swap(arr[j], arr[minIndex]);
        }
    }
    
    void MergeSort(KeyValue* arr, int s, int e)
    {
                if (s >= e)
                    return;
                int m = s + (e - s) / 2;
                MergeSort(arr, s, m);
                MergeSort(arr, m + 1, e);
                int i = s;
                int j = m + 1;
                int n = e - s + 1;
                KeyValue* tmp = new KeyValue[n];
                for (int c = 0; c < n; ++c)
                {
                    if (i <= m && (j > e || arr[i].key <= arr[j].key ) )
                        tmp[c] = arr[i++];
                    else
                        tmp[c] = arr[i++];
                }
                for (int c = 0; c < n; ++c)
                    arr[s + c] = tmp[c];
                delete[] tmp;
    }
    
    /**
	 * Sort the search table
	 */
	void Sort()
	{
//        SelectionSort(arr, n);
        
        MergeSort(arr, 0, n - 1);
        
	}
	
	//Number of elements in the SearchTable
	unsigned int n;
	//Capacity of arr
	unsigned int max;
	//The underlying array
	KeyValue* arr;
};
#endif