#include "List.h"

typedef unsigned int Index;

template <typename T>
class LinkedList : public List < T >
{
private:
	Node* head;
	int n;
public:
	class Node
	{
	public:
		T item;
		Node* next;
	};
	LinkedList(){
		head = NULL;
		n = 0;
		nxt = NULL;
	}
	LinkedList(int index, Node* start, Node* nxt){
		n = index;
		head = start;
		next = nxt;
	}
	virtual void Add(const T& ele){
		Node* ptr = new Node();
		ptr.item = ele;
		ptr.next = head;
		head = ptr;
		++n;
	}
	virtual unsigned int Size() const { return n; }
	virtual T& Get(Index i) const {
		Node*ptr = head;
		for (int j = 0; j < n - i - 1; ++j)
		{
			ptr = ptr->next;
			return ptr->item;
		}
	}
	virtual void Set(Index i, const T& val){
		Node* ptr = head;
		for (int j = 0; j < n - i - 1; ++i)
		{
			ptr = ptr->next;
		}
		ptr->item = val;
	}
	virtual void Remove(Index i)
	{
		if (Size() <= i)
		{
			throw BAD_INDX;
		}
		Node* ptr = head;
		if (i == 0)
		{
			head = head->next;
			delete ptr;
		}
		else
			for (int i = 0; i < n - i - 1; ++i)
			{
				ptr = ptr->next;
				Node* oldNode = ptr->next;
				if (oldNode == NULL)
				{
					ptr->next = NULL;
				}
				else
					ptr->next = oldNode->next;
				delete oldNode;
			}
		--n;
		}
	virtual void Clear(){
		while (Size() > 0)
		{
			Remove(0);
		}
	}
};
