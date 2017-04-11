#ifndef HEAP_H
#define HEAP_H
#include"Vector.h"
template<class T>
class Heap{
	public:
		Heap(const T&);
		void push(const T&);
		T pop();
		T peak();
		inline int size(){ return vec.size()-1;}
	private:
		Vector<T> vec;
		void swap(int,int);
};
template<class T>
Heap<T>::Heap(const T& min){
	vec.push_back(min);
} 
template<class T>
void Heap<T>::push(const T& toAdd){
	vec.push_back(toAdd);
	int index=vec.size()-1;
	for(;;){
		if(vec.get(index/2)>vec.get(index)){
			swap(index/2,index);
			index=index/2;
		}else{
			break;
		}
	}
}
template<class T>
void Heap<T>::swap(int i,int j){
	T temp{vec.get(i)};
	vec.set(i,vec.get(j));
	vec.set(j,temp);

}
template<class T>
T Heap<T>::pop(){
	if(size()<=0) return T{};
	T result{vec.get(1)};
	vec.set(1,vec.get(vec.size()-1));
	vec.remove_back();
	int index=1;
	for(;;){
		if(index*2>=vec.size()) break;
		if(index*2<vec.size()&&index*2+1>=vec.size()&&vec.get(index)>vec.get(index*2)) {
			swap(index,index*2);
			break;
		}
		if(index*2<vec.size()&&index*2+1<vec.size()){
			int temp=vec.get(index*2)<vec.get(index*2+1)?index*2:index*2+1;
			swap(temp,index);
			index=temp;
		}
	}
	return result;
}
template<class T>
T Heap<T>::peak(){
	return vec.get(1);
}
#endif 
