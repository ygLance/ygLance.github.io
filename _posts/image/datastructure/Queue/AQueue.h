template<typename E> class AQueue:public Queue<E>{
	private:
	int maxSize;
	int front;
	int rear;
	E* listArray;
	
	public:
	AQueue(int size=0){
		maxSize=size+1;
		rear=0;
		front=1;
		listArray=new E[maxSize];
	}
	~AQueue(){delete [] listArray;}
	
	void clear(){ rear=0;front=1;}
	
	void enqueue(const E&it ){
		if((rear+2)%maxSize==front){
			cout<<"Queue is full"<<endl;
			return;
		}
		rear=(rear+1)%maxSize;
		listArray[rear]=it;
	}
	
	E dequeue(){
		if(length()=0) {
			cout<<"Queue is empty"<<endl;
			return -1;
		}
		E it=listArray[front];
		front=(front+1)%maxSize;
		return it;
	}
	
	const E& frontValue() const{
		return listArray[front];
	}
	
	virtual int length() const{return (rear-front+maxSize+1)%maxSize;}
}