#ifndef  SUB_ALLOCOTOR_H
#define  SUB_ALLOCOTOR_H
#include<malloc.h>
#include<iostream>
#include<stdio.h>
using namespace std;
enum{  _MAX_BYTES =128 };
enum{   _MIN_BYTES=8   };
union obj{
	obj* next_free_list;
};

template<class T>
class Sub_alloctor{
	public:
		Sub_alloctor(){
			start_free=0;
			free_size=0;
			for(int i=0;i<16;++i)
				*(free_list+i)=0;
		}
		T* allocate(size_t);
		void deallocate(void* p, size_t);
		void trace(){
			cout<<"---------------------------"<<endl;
			for(int i=1;i<17;++i){
				cout<<i;
				obj* p=free_list[i-1];
				int j=0;
				while(p!=0&&j<30){
					j++;
					printf("  %x",p);
					p=p->next_free_list;
				}
				cout<<endl;
			}
		}
	
		obj* free_list[16];
		char* start_free;
		size_t free_size;
		void refill(obj** p,size_t);
		obj* chunk(size_t,int&);
		inline int index(size_t bytes){
			return bytes/_MIN_BYTES-1;
		}
};
template<class T>
T* Sub_alloctor<T>::allocate(size_t bytes){
	obj** target_list=(free_list+index(bytes));
	if((*target_list)==0){
		refill(target_list,bytes);
	}
	obj* re=*target_list;
	*target_list=(*target_list)->next_free_list;
	return (T*)re;
}
template<class T>
void Sub_alloctor<T>::deallocate(void *input,size_t bytes){
	obj* p=(obj*)input;
	*p=obj();
	obj** target_list=free_list+index(bytes);
	if(*target_list==0){
		*target_list=p;
	}else{
		p->next_free_list=	(*target_list)->next_free_list;
		(*target_list)->next_free_list=p;
	}
}
template<class T>
void Sub_alloctor<T>::refill(obj** head,size_t bytes){
	cout<<"start refill"<<endl;
//	cout<<bytes<<endl;
	int num=10;
	obj *p=chunk(10*bytes,num);
//	printf("%x  p\n",p);
		*head=p;
	cout<<"start link"<<endl;
//	cout<<sizeof(obj*)<<"  sieof(obj())  "<<sizeof(char*)<<endl;
	for(int i=0;i<num-1;++i){


		*p=obj();
		p->next_free_list=p+bytes/sizeof(obj);
		p+=bytes/sizeof(obj);
	}
	p->next_free_list=0;
	cout<<"end refill"<<endl;
}
template<class T>
obj* Sub_alloctor<T>::chunk(size_t bytes,int &num){

//  cout<<"start chunk"<<endl;
	obj* result=(obj*)start_free;
//	cout<<"looking for"<<bytes<<endl;
	size_t node_size=bytes/10;
//	cout<<"free size is"<<free_size<<endl;
	if(free_size<node_size){
//		cout<<"memory pool not enough"<<endl;

		if(free_size!=0){
			obj** target_list=free_list+index(free_size);
			*result=obj();
			result->next_free_list=(*target_list)->next_free_list;
			(*target_list)->next_free_list=result;
		}
		start_free=(char*)malloc(5*bytes);
//		printf("%x  start_free  %x  new start_free\n",start_free,start_free+80);
		if(start_free==0) cout<<"malloc false"<<endl;
		free_size=5*bytes;
		result=(obj*)start_free;
	}else{
		num=free_size/(node_size);
	}
	
	start_free+=node_size*(num);
	free_size-=node_size*(num);
//	printf("%x new_start_free\n",start_free);
//	cout<<bytes<<"bytes"<<endl;
//	cout<<free_size<<"free_size"<<endl;

	return result;
}
#endif
