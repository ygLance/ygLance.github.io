template <typename E> class LQueue:public Queue<E>{
	private:
	Link<E>* front;
	Link<E>* rear;
	int size;
	
	public:
	LQueue(){
		front=rear=new Link<E>();
		size=0;
	}
	~LQueue(){clear();}
	
	void clear(){
		while(front!=rear){
			Link<E>* temp=front;
			front=front->next;
			delete temp;
		}
		size=0;
		delete front;
	}
	
	void enqueue(const E&it){
		rear=rear->next=new Link<E>(it,nullptr);
		size++;
	}
	
	E dequeue(){
		Link<E>* temp=front;
		E it=front->element;
		front=front->next;
		delete temp;
		size--;
		return it;
	}
	
	const E& frontValue() const{
		return front->element;
	}
	
	int length() const{
		return size;
	}
}