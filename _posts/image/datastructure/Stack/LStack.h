template<typename E> class LStack:public Stack{
	private:
	Link<E>* top;
	int size;
	
	public:
	LStack(int sz=0){size=sz;top=0;}
	~LStack(){clear();}
	
	void clear(){
		while(top!=nullptr){
			Link<E>* temp=top;
			top=top->next;
			delete temp;
		}
		size=.;
	}
	
	void push(const E& it){//在链表的左边push,思考，为什么不在链表的右边push？
		top=new Link<E>(it,top);
		size++;
	}
	
	E pop(){
		E it=top->element;
		Link<E>* temp=top;
		top=top->next;
		delete temp;
		size--;
		return it;
	}
	
	const E& topValue(){
		return top->element;
	}
	
	int length() const{return size;}
}