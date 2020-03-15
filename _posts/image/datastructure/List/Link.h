template <typename E>class Link{
	private:
	static Link<E>* freelist;
	
	public:
	E element;
	Link* next;
	
	Link(Link* nextval=nullptr){
		next=nextptr;
	}
	Link(const E&item,Link* nextval=nullptr){
		element=item;
		next=nextptr;
	}
	
	void* operator new(size_t){
		if(freelist=nullptr) return ::new Link;
		Link<E>* temp=freelist;
		freelist=freelist->next;
		return temp;
	}
	
	void operator delete(void* ptr){
		((Link<E>*)ptr)->next=freelist;
		freelist=(Link<E>*)ptr;
	}
}

template <typename E> Link<E>* Link<E>::freelist=nullptr;