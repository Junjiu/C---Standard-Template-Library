#ifndef QUEUE_H
#define QUEUE_H
#include"Deque.h"
template<class T>
class Queue{
	public:
		Queue();
		void push(const T&);
		T pop();
		T peak();
		int size(){
			return deque.size();
		}
	private:
		Deque<T> deque;
};
template<class T>
Queue<T>::Queue(){
	
}
template<class T>
void Queue<T>::push(const T& toAdd){
    deque.push_front(toAdd);
}
template<class T>
T Queue<T>::pop(){
	T result{peak()};
	deque.remove_back();
	return result;
}
template<class T>
T Queue<T>::peak(){
	return deque.get(0);
}
#endif
