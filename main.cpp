#include<iostream>
#include"Vector.h"
#include"Alloctor.h"
#include"Deque.h" 
#include"Queue.h"
#include"Stack.h"
//#include "Deque.cpp"
#include"List.h"
#include"Heap.h"
#include"PriorityQueue.h"
//#include"HashTable.h"
#include"Rb_map.h"

class Bob{
	public:
	
		Bob(int i):v{}{
			v.push_back(i);
			v.push_back(2*i);
		}
		
		Vector<int> v;
};
Bob *p; 
void test_func();
using namespace std;
int main(){
	char a[5];
	scanf("%s",a); 
	cout<<a<<endl;
//   	Rb_map<int,int> tree;
//   	tree.insert(55,555);
//   	
//  	tree.insert(66,777);
//  	tree.insert(88,333);
//   	tree.insert(44,444);
//   	tree.insert(99,333);
// 	tree.insert(110,444);
//   	tree.insert(22,333);
//	tree.insert(111,333);
//	tree.insert(112,333);
//	tree.insert(113,333);
//   
////   	tree.insert(44,10000);
//	tree.remove(99);
//   	tree.show_tree();
   	
//   	Vector<int> v=tree.search(55);
//	for(int i=0;i<v.size();++i){
//		cout<<v.get(i)<<endl;
//	}
//	cout<<"++++++++++++++++++++"<<endl;
//		Vector<int> v1=tree.search(55);
//	for(int i=0;i<v1.size();++i){
//		cout<<v1.get(i)<<endl;
//	}
//	cout<<"++++++++++++++++++++"<<endl;
//	Vector<int>  v2=tree.search(44);
//	for(int i=0;i<v2.size();++i){
//		cout<<v2.get(i)<<endl;
//	}
//	cout<<"++++++++++++++++++++"<<endl;
//	Vector<int>  v3=tree.search(66);
//	for(int i=0;i<v3.size();++i){
//		cout<<v3.get(i)<<endl;
//	}
//	cout<<"++++++++++++++++++++"<<endl;
//
//	
	Vector<int> v;
	
}
void test_func()
{

}
	
    


