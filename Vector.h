#ifndef VECTOR_H
#define VECTOR_H 
#include<iostream> 
#include"Alloctor.h"
#define INIL_SIZE 5
template<class T>
class Vector{
	public:
		Vector();
		T get(int index);
		void set(int ,const T&);
		void push_back(const T&);
		void remove_back();
		inline int size(){ return size_num;}
		void clear();
		~ Vector();
	private :
		int size_num;
		int total_size;
		T* start;
		Alloctor<T> alloc;
		void extend();
		
};
template<class T>
Vector<T>::Vector(){
	size_num=0;
	total_size=INIL_SIZE;
	start=alloc.allocate(INIL_SIZE);
}
template<class T>
T Vector<T>::get(int index){
	if(index>=size()) return(T)0;
	return *(start+index);
}
template<class T>
void Vector<T>::set(int index,const T& toSet){
	if(index>=size()) return;
	*(start+index)=T{toSet};
}
template<class T>
void Vector<T>::push_back(const T& toAdd){
	if(size_num== total_size) extend();
	*(start+size())=T{toAdd};
	++size_num;
}
template<class T>
void Vector<T>::remove_back(){
	if(size_num==0) return;
	--size_num;
}
template<class T>
void Vector<T>::clear(){
	size_num=0;
}
template<class T>
void Vector<T>::extend(){
	T* new_start=alloc.allocate(2*total_size);
	for(int i=0;i<total_size;++i)
		*(new_start+i)=*(start+i);
	total_size*=2;
	alloc.deallocate(start,size());
	start=new_start;
}
template<class T>
Vector<T>::~Vector(){
	alloc.deallocate(start,size()); 
}
#endif
