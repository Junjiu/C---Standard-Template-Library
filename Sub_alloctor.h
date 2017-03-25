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
		T* allocate(size_t);
		void deallocate(void* p, size_t);
		void trace(){
			cout<<"---------------------------"<<endl;
			for(int i=1;i<17;++i){
				cout<<i;
				obj* p=free_list[i-1];
				while(p!=0){
					printf("  %x",p);
					p=p->next_free_list;
				}
				cout<<endl;
			}
		}
	private:
		static obj* free_list[16];
		static char* start_free;
		static size_t free_size;
		void refill(obj** p,size_t,size_t);
		obj* chunk(size_t);
		inline int index(size_t bytes){
			return bytes/_MIN_BYTES;
		}
};
template<class T>
obj* Sub_alloctor<T>::free_list[16];
template<class T>
char* Sub_alloctor<T>::start_free=0;
template<class T>
size_t Sub_alloctor<T>::free_size=0;
template<class T>
T* Sub_alloctor<T>::allocate(size_t bytes){
	obj** target_list=(free_list+index(bytes));
	if((*target_list)==0){
		refill(target_list,bytes,_MIN_BYTES*(index(bytes))+1);
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
void Sub_alloctor<T>::refill(obj** head,size_t bytes,size_t chunk_size){
	bytes*=10;
	obj *p=chunk(bytes);
		*head=p;

	for(int i=0;i<10;++i){
		*p=obj();
		p->next_free_list=p+chunk_size;
		p+=chunk_size;

	}
}
template<class T>
obj* Sub_alloctor<T>::chunk(size_t bytes){
	obj* result=(obj*)start_free;
	if(free_size<bytes){
		if(free_size!=0){
			obj** target_list=free_list+index(free_size);
			*result=obj();
			result->next_free_list=(*target_list)->next_free_list;
			(*target_list)->next_free_list=result;
			free_size=0;
		}
		start_free=(char*)malloc(5*bytes);
		free_size=5*bytes;
		result=(obj*)start_free;
	}
	start_free+=bytes;
	free_size-=bytes;
	return result;
}
