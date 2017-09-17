#ifndef STACK_H
#define STACK_H
#include"Deque.h"
template<class T>
class Stack{
	public:
		Stack();
		Stack(const T&);
		void push(const T&);
		T pop();
		T peak();
		inline int size(){
			return deque.size();
		}
	private:
		Deque<T> deque;
};
template<class T>
Stack<T>::Stack(){
}
template<class T>
void Stack<T>::push(const T& toAdd){
	deque.push_front(toAdd);
}
template<class T>
T Stack<T>::pop(){
	T result{peak()};
	deque.remove_front();
	return result;
}
template<class T>
T Stack<T>::peak(){
	return T{deque.get(deque.size()-1)};
}
#endif
