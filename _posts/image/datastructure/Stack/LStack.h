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
	
	void push(const E& it){//����������push,˼����Ϊʲô����������ұ�push��
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