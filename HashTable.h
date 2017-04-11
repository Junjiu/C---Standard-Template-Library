#ifndef HASHTABLE_H
#define HASHTABLE_H
#include"Alloctor.h"
#include"HashFunc.h"
#include"Vector.h"
#include"List.h"
#define init_size 5
#include<iostream>
template<class T>
class t_node{
	public:
		t_node(int k,const T& e):key(k),elem(e){
		}
		t_node(const t_node& init):key(init.key),elem(init.elem){
		};
		t_node(){
		};
		int key;
		T elem;
};
template<class K,class E >
class HashTable{
	public:
		HashTable(){
			init();
			size_num=0;
		};
		int size(){
			return size_num;
		}
		void put(K,E);
		E get(K);
		
	private:
	    void init();
		int vaild_size=init_size;
		int size_num;
		Alloctor<List<t_node<E>>> alloc;
		void extend();
		Vector<List<t_node<E>>*> v;
		inline int posit(int input){
			return input%vaild_size;
		}
};
template<class K,class E>
void HashTable<K,E>::extend(){
	t_node<E> temp[size_num];
	for(int i=0,k=0;i<v.size();++i){
		for(int j=0;j<(*v.get(i)).size();++j){
			temp[k++]=(*v.get(i)).get(j);
		}
	}
	v.clear();
	vaild_size*=3;
	init();
	for( t_node<E> node:temp){
		put(node.key,node.elem);
		size_num--;
	}
} 
template<class K,class E>
void HashTable<K,E>::init(){
			for(int i=0;i<vaild_size;++i){
		  	auto p=alloc.allocate(1);
			v.push_back(p);
			*(p)=List<t_node<E>>();
			}
}
template<class K,class E>
void HashTable<K,E>::put(K key,E elem){
	int p=posit(hash_func(key));
	t_node<E> node=t_node<E>(key,elem);
	(*v.get(p)).add(node);
	size_num++;
	if(size_num>2*vaild_size) extend();
}
template<class K,class E>
E HashTable<K,E>::get(K key){
 int hash_code=hash_func(key);
 int p=posit(hash_code);
 List<t_node<E>> list=*v.get(p);
 for(int i=0;i<list.size();++i){
 	if(list.get(i).key==hash_code)
 		return list.get(i).elem;
 }
 return E{};
}

#endif
