template <typename E> class List{
	private:
	void operator=(const List&){} //protect assignment why?
	List(const List&) {}//protect copy constructor
	
	public:
	List(){}
	virtual ~List(){}
	
	virtual void clear()=0;//clear contents from the lists,to make it empty
	
	virtual void insert(const E& item)=0;
	
	virtual void append(const E& item)=0;//add a element in the end of the list
	
	virtual E remove()=0;//remove the current element
	
	virtual void moveToStart()=0;
	
	virtual void moveToEnd()=0;
	
	virtual void prev()=0;
	
	virtual void next()=0;
	
	virtual int length() const=0;
	
	virtual int currPos() const=0;
	
	virtual void moveToPos(int pos)=0;
	
	virtual const E& getValue() const=0;
	
}