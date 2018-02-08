#ifndef TREEMAP_H
#define TREEMAP_H

/**
 *
 */
template <typename T>
class BinarySearchTree
{
public:
    //Defines an error code used for throwing
    //integer exceptions
    const static int ELE_DNE = -2467;

    BinarySearchTree() {
//        root = new Node();
        n = 0;
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree& cpyBST) {
        n = 0;
    }

    /**
     * Attempts to find the corresponding value
     * for a given key. The int ELE_DNE is thrown
     * if the key is not in the map
     * @param k Is the key to search for
     * @return The value corresponding to k
     */
    T& Find(const T& v) const
    {	//Attempt to find the element
        Node* p = find(root, v);
        if (p == NULL)
            throw ELE_DNE;
        return p->val;
    }

    void Remove(const T& val) {
        remove(root, val);
        --n;
    }

    /**
     * Adds a (key, value) pair to the map
     * @param k Is the key
     * @param v Is the value
     */
    void Insert(const T& v)
    {
        Node*& ptr = const_cast<Node* &> (find(root, v));
        ptr = new Node(v);
        ++n;
    }

    /**
     * Returns the number of elements in the Map
     * @return: Number of elements in map object
     */
    unsigned int Size() const
    {
        return n;
    }


private:
    class Node
    {
    public:
        Node() { right = left = NULL; }
        Node(const T& v) {
            right = left = NULL;
            val = v;
        }
        
        Node* right;
        Node* left;
        T val;
    };

    //The root of the tree and the number of children (n)
    Node* root;
    unsigned int n;

    /**
     * Helper function for Find
     * @param ptr is the root node of tree to search
     * @param v is the value to search for
     * @return The node that corresponds to v
     */
    Node* const& find(Node* const& ptr, const T& v) const {
        bool test = ptr == NULL;                        // test
        if (ptr == NULL || v == ptr->val)
            return ptr;
        else if (v < ptr->val)
            return find(ptr->left, v);
        return find(ptr->right, v);
    }

    Node* FindMinNode(Node*p)
    {
        while (p->left != NULL)
            p = p->left;
        return p;
    }

    /**
     * Attempts to erase the (key, value) pair
     * with key  = k. The int ELE_DNE is thrown
     * if the key is not in the map
     * @param k Is the key of the pair to erase
     */
    void remove(Node*& ptr, const T& val)
    {
        Node* &node = const_cast<Node* &> (find(ptr, val));
        if (node == NULL)
            throw ELE_DNE;
        if (node->right != NULL && node->left != NULL) {
            Node* tmp = FindMinNode(node->right);
            node->val = tmp->val;
            remove(node->right, node->val);
        }
        else if (node->right != NULL) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
        }
        else if (node->left != NULL) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
        }
        else {
            delete node;
            node = NULL;
        }
    }

};

/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using a binary
 * search tree. T1 is the 
 * type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class TreeMap : public Map<T1, T2>
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
        KeyValue kv = KeyValue();
        kv.key = k;
        
        try {
            bst.Remove(kv);
        } catch (int e) {
            if (e == -2467)
                std::cout << "TreeMap: ELE_DNE; failed to erase";
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
	{	//Attempt to find the element
        KeyValue kv = KeyValue();
        kv.key = k;
        
//        KeyValue rkv = bst.Find(kv);
//        return rkv.value;                   //I think this is where the error is. Don't know how to fix
        
        try {
            return bst.Find(kv).value;
        } catch (int e) {
            if (e == -2467)
                std::cout << "TreeMap: ELE_DNE; failed to find";
        }
        return bst.Find(kv).value;
	}

	/**
	 * Overloaded assignment operator. Perform
	 * a deep copy of the parameter.
	 * @param rhs The object to copy
	 * @return A reference to the calling object
	 */
	TreeMap& operator=(const TreeMap& rhs)
	{
        bst = BinarySearchTree< KeyValue >(rhs.bst);
        return bst;
	}
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v)
	{
        KeyValue kv = KeyValue(k, v);
//        kv.key = k;
//        kv.value = v;
        
        bst.Insert(kv);
	}

	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	virtual unsigned int Size() const
	{	
        return bst.Size();
	}
	
	//Default constructor
	TreeMap()
	{
		bst = BinarySearchTree< KeyValue >();
	}
	
	//Copy constructor
	TreeMap(const TreeMap& tm)
	{
		bst = BinarySearchTree< KeyValue >(tm.bst);
	}
	
	//Virtual destructor
	virtual ~TreeMap()
	{
		bst.~BinarySearchTree< KeyValue >();
	}
	  
private:
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
        
        KeyValue()
        {
            
        }
        
        KeyValue(const T1& k, const T2& v)
        {
            key = k;
            value = v;
        }
        
//        friend bool operator==(const KeyValue& lhs, const KeyValue& rhs) {
//            return lhs.key == rhs.key;
//        }
        
        bool operator==( const KeyValue& rhs) const {
            return this->key == rhs.key;
        }
        
        bool operator<(const KeyValue& rhs) const {
            return this->key < rhs.key;
        }
        
        KeyValue& operator=(const KeyValue& rhs){
            this->key = rhs.key;
            this->value = rhs.value;
            
            return *this;
        }
	};
	//BST implementation goes here
    BinarySearchTree< KeyValue > bst;
//	/**
//	* This class represents a node in the search tree
//	*/
//	class Node
//	{
//	public:
//		Node() { right = left = NULL; }
//		Node* right;
//		Node* left;
//		KeyValue val;
//	};
//	//The root of the tree and the number of children (n)
//	Node* root;
//	unsigned int n;
};
#endif