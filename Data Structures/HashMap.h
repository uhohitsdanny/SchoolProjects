#ifndef HASHMAP_H
#define HASHMAP_H
//Needed for rand() function
#include <cstdlib>
typedef unsigned int Index;
/**
 * A map implementation that uses a  hash table
 * with a multiplicative hash function internally. 
 */
template <typename T1, typename T2>
class HashMap : public Map<T1, T2>
{
public:	
	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	virtual void Erase(const T1& k)
	{
        int i = F(k);
        int j = i;
        
        while (true) {
            if (arr[j].open)
                throw Map<T1, T2>::ELE_DNE;
            else if (arr[j].key == k) {
                arr[j].open = true;
                Rehash(max);
                break;
            }
            j = (j + 1) % max;
            if (i == j)
                throw Map<T1, T2>::ELE_DNE;
        }
	}

	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	virtual T2& Find(const T1& k) const
	{	
        int i = F(k);
        int j = i;
        
        while (true) {
            if (arr[j].open)
                throw Map<T1, T2>::ELE_DNE;
            else if (arr[j].key == k)
                return arr[j].val;
            j = (j + 1) % max;
            if (i == j)
                throw Map<T1, T2>::ELE_DNE;
        }
	}
	
	/**
	* Create a map with a default initial
	* capacity
	*/
	HashMap()
	{
        n = 0;
        max = DEF_CAPC;
        
        srand(time(NULL));
        a = rand();
        b = rand();
        
        arr = new KeyValue[max];
	}
	
	
	/**
	* Create a map with a initial capacity
	* @param capc The initial capacity
	*/
	HashMap(unsigned int capc)
	{
        n = 0;
        max = capc;
        
        srand(time(NULL));
        a = rand();
        b = rand();
        
        arr = new KeyValue[max];
	}
	
	//Copy constructor
	HashMap(const HashMap& hm)
	{
        if (this == &hm)
            return;
        
        n = 0;
        max = hm.max;
        
        srand(time(NULL));
        a = rand();
        b = rand();
        
        arr = new KeyValue[max];
        
        for (int i = 0; i < max; ++i)
            if (!hm.arr[i].open)
                Put(hm.arr[i].key, hm.arr[i].value);
	}
	
	//Desctructor 
	virtual ~HashMap() 
	{ 
		delete [] arr;
	}
	
	/**
	 * Overloaded assignment operator. Perform
	 * a deep copy of the parameter.
	 * @param rhs The object to copy
	 * @return A reference to the calling object
	 */
	HashMap& operator=(const HashMap& rhs)
	{
        if (this == &rhs)
            return *this;
        delete[] arr;
        n = 0;
        max = rhs.max;
        arr = new KeyValue[max];
        for (int i = 0; i < max; ++i)
            if (!rhs.arr[i].open)
                Put(rhs.arr[i].key, rhs.arr[i].value);
        return *this;
	}
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v)
	{
        if ((n + 1.0)/max >= 0.5)
            Rehash(max * 2);
        
        int i = F(k);
        
        KeyValue kv = KeyValue(k, v);
        
        while (true) {
            if (arr[i].open) {
                arr[i] = kv;
                arr[i].open = false;
                break;
            }
            i = (i + 1) % max;
        }
        ++n;
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
	//Default capacity of the underlying array
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
		KeyValue()
		{	//Mark the entry as being open
			open = true;
		}
        KeyValue(const T1& k, const T2& v)
        {
            key = k;
            val = v;
            open = true;
        }
		//The key
		T1 key;
		//The value
		T2 val;
		//Whether the entry is open
		bool open;
	};
    
    /**
	* Resize the map's array the requiring a 
	* rehash. A new random hash function is computed.
	* @param The new size of the array
	*/
	void Rehash(unsigned int cap)
	{	//Don't forget to create a new hash function
        srand(time(NULL));
        a = rand();
        b = rand();
        
        unsigned int oldMax = max;
        KeyValue* tmp = arr;
        max = cap;
        arr = new KeyValue[max];
        n = 0;
        for(unsigned int i = 0; i < oldMax; ++i)
            if(tmp[i].open == false)
                Put(tmp[i].key, tmp[i].val);
	}

	/**
	* The hash function
	* @param The element to be hashed
	* @return The resulting hash index
	*/
	Index F(const T1& ele) const
	{
		return (a * ele + b) % max;
	}
	//The hash table
	KeyValue* arr;
	//Number of elements, capcity, and hash function values
	unsigned int n, max, a, b;
};
#endif