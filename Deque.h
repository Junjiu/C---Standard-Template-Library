#ifndef DEQUE_H
#define DEQUE_H
#include"Alloctor.h"
#include<iostream>
#define INIT_SIZE 5
#define CHUNK_SIZE 10
#define BACK = 0;
#define  Front = 1;
template<class T>
class Deque{
	public:
	
		Deque();
		T get(int); 
		void push_back(const T&);
		void push_front(const T&);
		inline int size(){  return size_num;	}
		void remove_front();
		void remove_back();
	private:
		T** map_start;
		T** deallo_helper;
		inline int chunk_num() { return front_size+back_size+1 ;}
		int front_chunk_end;
		int	back_chunk_end;
		
		int front_free_chunk;
		int back_free_chunk;
		
		int front_size;
		int back_size;
		
		int size_num;
		
		int space;
		int back_num;
		Alloctor<T*> t_allo;
		Alloctor<T> tp_allo;
		void extend();
};
template<class T>
Deque<T>::Deque(){
	map_start=t_allo.allocate(INIT_SIZE)+INIT_SIZE/2;
	deallo_helper=map_start-INIT_SIZE/2;
	space=INIT_SIZE;
//	cout<<"T_Alloctor working --from Deque"<<endl;
	*(map_start)=tp_allo.allocate(CHUNK_SIZE);
//	cout<<"TP_Alloctor working --from Deque"<<endl;
	front_free_chunk=INIT_SIZE/2;
	back_free_chunk=INIT_SIZE/2;
	front_size=0;
	back_size=0;
	front_chunk_end=0;
	back_chunk_end=0;
	size_num=1;
	back_num=0;
	**map_start=T{};
	remove_back();
//	cout<<"finish initalization"<<endl;
}
template <class T> 
void Deque<T>::push_front(const T& toAdd){
	if(front_chunk_end==CHUNK_SIZE-1){
		if(front_free_chunk==0) extend();
		front_free_chunk--;
		front_chunk_end=0;
		front_size++;
		*(map_start+front_size)=tp_allo.allocate(CHUNK_SIZE);
	}else{
		front_chunk_end++;
	}
	*(*(map_start+front_size)+front_chunk_end)=T{toAdd};
	size_num++;
}
template <class T> 
void Deque<T>::push_back(const T& toAdd){
	if(back_chunk_end==0){
		if(back_free_chunk==0) extend();
		back_free_chunk--;
		back_chunk_end=CHUNK_SIZE-1;
		back_size++;
		*(map_start-back_size)=tp_allo.allocate(CHUNK_SIZE);
	}else{
		back_chunk_end--;
	}
//	cout<<"=========push_back==============="<<endl;
//	cout<<back_size<<"  back_size"<<endl;
//	cout<<back_chunk_end<<"  back_chunk_end"<<endl;
//	cout<<toAdd<<"   toAdd"<<endl;
//	cout<<printf("%x    Address:\n",(*(map_start-back_size)+back_chunk_end));
	*(*(map_start-back_size)+back_chunk_end)=T{toAdd};
	size_num++;
	back_num++;
}
template<class T>
void Deque<T>::extend(){
//	cout<<"start extend!!!"<<endl;
//	cout<<"memory pool: "<<t_allo.sub_alloctor.free_size<<endl;
//	cout<<"number:"<<3*chunk_num()<<endl;
	int num=chunk_num();
	T** new_start=t_allo.allocate(3*num)+num;
	front_free_chunk+=num;
	back_free_chunk+=num;
	for(int i=-1*back_size,j=0;i<=front_size;++i,++j){
		*(new_start+j)=*(map_start+i);
	}
	t_allo.deallocate(deallo_helper,space);
	space*=3;
	deallo_helper=new_start-num;
	map_start=new_start+back_size;
//	cout<<"finish extend!!"<<endl;
}
template<class T>
void Deque<T>::remove_front(){
	if(size()==0) return;
	if(front_chunk_end==0){
		tp_allo.deallocate(*(map_start+front_size),CHUNK_SIZE);
		front_chunk_end=CHUNK_SIZE-1;
		front_size--;
		front_free_chunk++;
	}else{
		front_chunk_end--;
	}
	size_num--;
}
template<class T>
void Deque<T>::remove_back(){
	if(size()==0) return;
	if(back_chunk_end==CHUNK_SIZE-1){
//		cout<<"one chunk is being moving"<<endl;
		tp_allo.deallocate(*(map_start-back_size),CHUNK_SIZE);
		back_chunk_end=0;
		back_size--;
		back_free_chunk++;
	}else{
		back_chunk_end++;
	}
	size_num--;
	back_num--;
}
template<class T>
T Deque<T>::get(int index){
	if(index<0||index>=size()) return T{};
	int target_chunk=0;
	int target_end=0;
	if((index-back_num)<0){
		target_chunk=(index-back_num+1)/(CHUNK_SIZE)-1;
		target_end=CHUNK_SIZE+(index-back_num)%CHUNK_SIZE;
		if(target_end==CHUNK_SIZE) target_end=0;
	} 
    else {
    	target_chunk=(index-back_num)/(CHUNK_SIZE);
    	target_end=(index-back_num)%CHUNK_SIZE;
	}	
//	cout<<target_chunk<<"target_chunk"<<endl;
//	cout<<target_end<<"target_end"<<endl;
//	cout<<index-back_num<<"index"<<endl;
//    printf("%x  Address  \n",(*(map_start+target_chunk)+target_end));
	return *(*(map_start+target_chunk)+target_end);
}

#endif
