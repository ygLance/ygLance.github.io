template <typename E> class AStack:public Stack<E>{
	private:
	int maxSize;
	int top;
	E *listArray;
	
	public:
	AStack(int size=0){
		maxSize=size;
		top=0;
		listArray=new int[maxSize];
	}
	~AStack(){delete [] listArray;}
	
	void clear(){
		delete[] listArray;
		listArray=new int[maxSize];
		top=0;
	}
	
	void push(const E&it ){
		if(top>=maxSize-1) {
			cout<<"no space"<<endl;
			return;
		}
		listArray[++top]=it;
	}
	
	E pop(){
		assert(top>=0,"no element");
		return listArray[top--];
	}
	
	const E& topValue(){
		assert(top>=0,"no element");
		return listArray[top];
	}
	
	int length() const{
		return top+1;
	}
	
}