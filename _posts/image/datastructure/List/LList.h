template <typename E> class Link{
	public:
	E element;
	Link *next;
	
	Link(){
		next=nullptr;
	}
	Link(const E&item){
		element=item;
		next=nullptr;
	}
	Link(const E&item,Link* nextval){
		element=item;
		next=nextval;
	}
	Link(Link* nextval){
		next=nextval;
	}
}

template <typename E> class LList:public List<E>{
	private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int size;
	
	void init(){
		curr=tail=head=new Link<E>;
		cnt=0;
	}
	
	void removeall(){
		while(head!=nullptr){
			curr=head;
			head=head->next;
			delete curr;
		}
	}
	
	public:
	LList(){init();}
	LList(int length){
		init();
		cnt=length;
		int temp=cnt-1;
		while(temp--){
			append();
		}
	}
	
	void clear(){
		removeall();
		init();
	}
	
	void insert(const E&item){
		Link<E>* temp=new Link<E>(item,curr->next);
		curr->next=temp;
		if(tail==curr) tail=temp;
		size++;
	}
	
	void append(){
		tail->next=new Link<E>(0,nullptr);
		tail=tail->next;
		cnt++;
	}
	void append(const E&item){
		tail=tail->next=new Link<E>(item,nullptr);
		cnt++;
	}
	
	E remove(){//remove curr->next
	    assert(curr!=tail,"No,element"); 
		E temp=curr->next->element;
		if(curr->next==tail){
			curr->next=nullptr;
			delete tail;
			tail=curr;
			cnt--;
		}
		else{
			Link<E>* ltemp=curr->next;
			curr->next=curr->next->next;
			delete ltemp;
			cnt--;
		}
		return temp;
	}
	
	void moveToStart(){
		curr=head;
	}
	
	void moveToEnd(){
		curr=tail;
	}
	
	void prev(){
		if(curr==head) return;
		Link<E>* temp=head;
		while(temp->next!=curr)
			temp=temp->next;
		curr=temp;
	}
	
	void next(){
		if(curr==tail) return;
		curr=curr->next;
	}
	
	int length() const{
		return size;
	}
	
	int currPos() const{
		Link<E>* temp=head;
		int cnt=0;
		while(temp!=curr){
			temp=temp->next;
			cnt++;
		return cnt;
	} 
	
	void moveToPos(int pos){
		Link<E>* temp=head;
		while(pos--){
			temp=temp->next;
		}
		curr=temp;
	}
	
	const E& getValue() const{
		return curr->element;
	}
}