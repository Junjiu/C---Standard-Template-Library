#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include"Heap.h"
template<class T>
class PriorityQueue{
	public:
		
		PriorityQueue(const T&);
		void push(const T&);
		T pop();
		T peak();
		int size();
	private:
		Heap<T> heap;
};
template<class T>
PriorityQueue<T>::PriorityQueue(const T& init):heap(init){
}
template<class T>
void PriorityQueue<T>::push(const T& toAdd){
	heap.push(toAdd);
}
template<class T>
T PriorityQueue<T>::pop(){
	return heap.pop();
}
template<class T>
T PriorityQueue<T>::peak(){
	return heap.peak();
}
template<class T>
int PriorityQueue<T>::size(){
	return heap.size();
}


#endif
