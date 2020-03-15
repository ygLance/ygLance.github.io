#include "List.h"
template <typename E> class AList:public List<E>{
	private:
	int maxSize;
	int listSize;
	int curr;
	E* listArray;
	
	public:
	AList(){}
	AList(int size){
		maxSize=size;
		listSize=0;
		curr=0;
		listArray=new E[maxSize];
	}
	~AList(){ delete [] listArray;}
	
	void clear(){
		delete [] listArray;
		curr=listSize=0;
		listArray=new E[maxSize];
	}
	
	bool check(){
		if(listSize>maxSize||listSize<0) {
			cout<<"out of range"<<endl;
			return true;
		}
	}
	
	//time complexity:O(n)
	void insert(const E& item){
		listSize++;
		if(check()) return;
		for(int cnt=listSize-1;cnt>curr;cnt--){
			listArray[cnt]=listArray[cnt-1];
		}
		listArray[curr]=item;
		return;
	}
	
	//time complexity:O(1)
	void append(const E&item){
		listSize++;
		if(check()) return;
		listArray[listSize-1]=item;
	}
	
	//time complexity:O(n)
	E remove(){
		int temp=listArray[cnt];
		listSize--;
		if(check()) return NULL;
		for(int cnt=curr;cnt<listSize;cnt++){
			listArray[cnt]=listArray[cnt+1];
		}
		return temp;
	}
	
	//time complexity:O(1)
	void moveToStart(){
		curr=0;
	}
	
	void moveToEnd(){
		curr=listSize;
	}
	
	void next(){
		if(curr>=listSize-1) cout<<"out of range"<<endl;
		curr++;
	}
	
	void prev(){
		if(curr<=0) cout<<"out of range"<<endl;
		curr--;
	}
	
	int length(){ return listSize;}
	int currPos(){return curr;}
	
	void moveToPos(int pos){
		if(pos<=0||pos>=listSize) cout<<"out of range"<<endl;
		curr=pos;
	}
	
	const E& getValue() const{
		if(listSize<=0) cout<<"No current element"<<endl;
		return listArray[curr];
	}

	void print() const{
		for (int cnt = 0; cnt < listSize; cnt++) {
			cout << listArray[cnt] << " ";
		}
		cout << endl;
	}
}