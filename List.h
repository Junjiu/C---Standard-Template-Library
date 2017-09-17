#ifndef LIST_H
#define LIST_H
#include "Alloctor.h"
#include<iostream>
using namespace std;
template<class T>
class Node{
	public:
	Node();
	Node(const T&);
	Node * next;
	T elem;
};
template<class T>
Node<T>::Node(const T& init):elem{init}{
	next=0;
}
template<class T>
Node<T>::Node():elem{}{
	next=0;
}
template<class T>
class List{
	public:
		List();
		
		void insert(const T&,int);
		void remove(int );
		void add(const T&);
		T get(int );
		inline int size(){ return size_num; }
	private:
		int size_num;
		Node<T>* getNode(int);
		Node<T>* head;
		Alloctor<Node<T>> allo;
};
template<class T>
List<T>::List(){
	head=allo.allocate(1);
	*head=Node<T>();
	size_num=0;
}
template<class T>
void List<T>::insert(const T& toAdd,int index){
	if(index>size()||index<0) return;
	Node<T> *p=allo.allocate(1);
	*p=Node<T>{toAdd};
	Node<T> *node_before=getNode(index);
	p->next=node_before->next;
	node_before->next=p;
	size_num++;
	
}
template<class T>
void List<T>::add(const T& toAdd){
	insert(toAdd,size());
}
template<class T>
void List<T>::remove(int index){
	if(index>=size()||index<0) return;
	Node<T> *node_before=getNode(index);
	auto *p=node_before->next;
	node_before->next=p->next;
	allo.deallocate(p,1);
	size_num--;
}
template<class T>
T List<T>::get(int index){
	if(index<0||index>=size()) return T{};
	return getNode(index)->next->elem;
}
template<class T>
Node<T>* List<T>::getNode(int index){
	auto p=head;
	for(int i=0;i<index;++i){
		p=p->next;
	}
	return p;
}
#endif
