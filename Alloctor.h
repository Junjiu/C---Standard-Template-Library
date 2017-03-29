#ifndef ALLOCTOR_H
#define ALLOCTOR_H
#include<malloc.h>
#include<iostream>
#include"Sub_alloctor.h"
#define _BAD_ALLOC cout<<"out of memory"<<endl;exit(1)
using namespace std;
template <class T>
class Alloctor {
	public:
	T* allocate(int);
	void deallocate(T*,int );
	void trace(){
		sub_alloctor.trace();
	}
	
	inline void destory(T* p){
		p->~T();
	}
	inline size_t ROUND_UP(size_t bytes){
		return (bytes%_MIN_BYTES==0)?(bytes):(bytes/_MIN_BYTES*_MIN_BYTES+_MIN_BYTES);
	}
	Sub_alloctor<T> sub_alloctor;
};
template <class T>
T* Alloctor<T>::allocate(int n){
	
	size_t bytes=ROUND_UP(n*sizeof(T));
	T* result;
	if(bytes<=_MAX_BYTES){
		result=sub_alloctor.allocate(bytes);
	}else{
		result=(T*)malloc(bytes);
	}
	if(result==0) {
		_BAD_ALLOC;
	}
	
	return result;
}
template <class T>
void Alloctor<T>::deallocate(T* p,int n){
	size_t bytes=n*sizeof(T);
	for(int i=0;i<n;++i){
		destory(p+i);	
	}
	if(bytes>_MAX_BYTES){
		free(p);
	}else{
		sub_alloctor.deallocate(p,bytes);
	}
}
#endif
