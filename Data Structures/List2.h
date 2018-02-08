typedef unsigned int Index;
template < typename T >
class List
{
public:
	const static int BAD_INDX = -1;

	virtual void Add(const T& ele) = 0;
	virtual void Clear() = 0;
	virtual T& Get(Index i) const = 0;
	virtual void Set(Index i, const T& val) = 0;
	virtual void Remove(Index i) = 0;
	virtual unsigned int Size() const = 0;
	virtual ~List() {};
};