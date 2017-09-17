#ifndef RB_MAP_H
#define RB_MAPp_H
#include"HashFunc.h"
#include"Vector.h"
#include"Alloctor.h"
#define RED  0
#define BLACK 1
#define RIGHT 0
#define LEFT 1
template<class K,class E>
class rb_node{
	public:
		rb_node(K k):key(hash_func(k)){
			left=0;
			right=0;
			parent=0;
			color=RED;
			
		}
		~rb_node(){
			v.~Vector();
		}
		rb_node<K,E> *left;
		rb_node<K,E> *right;
		rb_node<K,E> *parent;
		Vector<E> v;
		int key;
		bool color;
};
template<class K,class E>
class Rb_map{
	public:
		Rb_map(){}
		void show_tree();
		void insert(K,E);
		Vector<E> search(K);// if there is not this key in the rb tree, it will return a empty vector.
		void remove(K);
		
		void remove_helper(rb_node<K,E> *,rb_node<K,E>*,bool );
		void Show_tree_helper(rb_node<K,E>*,int,int);
		Alloctor<rb_node<K,E>> alloc;
		void adjust(rb_node<K,E>*);
		void left_rotation(rb_node<K,E>*);
		void right_rotation(rb_node<K,E>*);
		rb_node<K,E>* victim(rb_node<K,E> *);
		inline rb_node<K,E>* sibling(rb_node<K,E> * node){
			return node->parent->left==node?(node->parent->right):(node->parent->left);
		}
		inline bool is_black(rb_node<K,E> *p){
			if(p==0||p->color==BLACK)
				return 1;
			else
				return 0;
		}
		rb_node<K,E>* head=0;
};
template<class K,class E>
rb_node<K,E>* Rb_map<K,E>::victim(rb_node<K,E>* node){
	if(node->right!=0){
		node=node->right;
	}else{
		return node;
	}
	while(node->left!=0){
		node=node->left;
	}
	cout<<"victim is:  "<<node->key<<endl;
	return node;
}
template<class K,class E>
void Rb_map<K,E>::show_tree(){
	Show_tree_helper(head,0,0);
}
template<class K,class E>
void Rb_map<K,E>::Show_tree_helper(rb_node<K,E>* node,int deep,int side){
	if(node==0) return;
	for(int i=0;i<deep;++i){
		cout<<"  ";
	}
	if(side)
		cout<<"left   ";
	else
		cout<<"right  ";
	cout<<"Key:"<<node->key<<"     "<<node->color<<"     elements:";
	for(int i=0;i<node->v.size();++i){
		cout<<node->v.get(i)<<" ";
	}
	if(node->parent!=0){
		cout<<"  Parent: "<<node->parent->key<<endl;
	}
	cout<<endl;
	Show_tree_helper(node->left,deep+1,1);
	Show_tree_helper(node->right,deep+1,0);
	
}
template<class K,class E>
void Rb_map<K,E>::left_rotation(rb_node<K,E>* node){
	if(node==head){
		head=node->right;
		node->right->parent=0;
	}
	else{
			node->parent->right=node->right;
			node->right->parent=node->parent;
	}
	node->parent=node->right;
	node->right=node->right->left;
	if(node->right!=0) node->right->parent=node;
	node->parent->left=node;
	
}
template<class K,class E>
void Rb_map<K,E>::right_rotation(rb_node<K,E>* node){
	if(node==head){
		head=node->left;
		node->left->parent=0;
	}
	else{
			node->parent->left=node->left;
			node->left->parent=node->parent;
	}
	node->parent=node->left;
	node->left=node->left->right;
	if(node->left!=0) node->left->parent=node;
	node->parent->right=node;
	cout<<"reach the end of the rotation"<<endl;
}
template<class K,class E>
Vector<E> Rb_map<K,E>::search(K k){
	int key=hash_func(k);
	rb_node<K,E>* node=head;
    while(node!=0){
    	if(key==node->key) {
    		return node->v;
		}
    	if(key<node->key) {
    		node=node->left;
		}
    	else{
    		node=node->right;
		}
	}
	return Vector<E>();
}
template<class K,class E>
void Rb_map<K,E>::insert(K k, E element){
	int key=hash_func(k);
	if(head==0){
		head=alloc.allocate(1);
		*head=rb_node<K,E>(key);
		(*head).v.push_back(element);
		head->color=BLACK;
		return;
	}
	rb_node<K,E> ** result=0;
    rb_node<K,E>* node=head;
    while(1){
    	if(key==node->key) {
    		(*node).v.push_back(element);
    		return;
		}
    	if(key<node->key) {
    		if(node->left==0) {
    			result=&node->left;
    			break;
			}
    		node=node->left;
		}
    	else{
    		if(node->right==0) {
    			result=&node->right;
    			break;
			}
    		node=node->right;
		}
	}
	*result=alloc.allocate(1);
	**result=rb_node<K,E>(key);
	(*result)->v.push_back(element);
	(*result)->parent=node;
	
	if(node->color==BLACK) return;
	rb_node<K,E> *sib=sibling(node);
	
	while(sib!=0&&sib->color==RED){
		node->color=BLACK;
		sib->color=BLACK;
		if(node->parent!=head){
			node->parent->color=RED;
		}else{
			return;
		}
		node=node->parent;
		sib=sibling(node);
	}
	node->parent->color=RED;
	node->color=BLACK;
	if(node==node->parent->left){
		if((*result)==node->right)
			left_rotation(node);
		cout<<"reach the last rotation"<<endl;
		right_rotation(node->parent);
		return;
	}
	if(node==node->parent->right){
		if((*result)==node->left)
			right_rotation(node);
		left_rotation(node->parent);
		return;
	}
	
}
template<class K,class E>
void Rb_map<K,E>::remove(K k){
	int key=hash_func(k);
	rb_node<K,E>* result=0; 
	rb_node<K,E>* node=head;
    while(node!=0){
    	if(key==node->key) {
    		result=node;
    		break;
		}
    	if(key<node->key) {
    		node=node->left;
		}
    	else{
    		node=node->right;
		}
	}
	if(result==0) return;
	rb_node<K,E>* temp=victim(result);
	if(temp!=result){
		result->v.clear();
		for(int i=0;i<temp->v.size();++i){
			result->v.push_back(temp->v.get(i));
		}
		result->key=temp->key;
	}
	bool side=0;
	result=temp;

	if(result->left!=0&&result->right==0){
		if(result==head){
			head=result->left;
			if(head->color==RED)
				head->color=BLACK;
			return;
		}else{
			if(result->parent->right==result){
				result->parent->right=result->left;
				side=RIGHT;
			}
			else {
				result->parent->left=result->left;
				side=LEFT;
			}
				
			result->left->parent=result->parent;
				if(is_black(result)){
			if(is_black(result->right))
				remove_helper(result->right,result->parent,side);
			else
				result->right->color==BLACK;
			}
		}
	}else{
		if(result->parent->right==result){
			
			result->parent->right=result->right;
			side=RIGHT;
		}
		else {
			result->parent->left=result->right;
			side=LEFT;
		}
		if(result->right!=0) result->right->parent=result->parent;
		if(is_black(result)){
			if(is_black(result->right))
				remove_helper(result->left,result->parent,side);
			else
				result->right->color==BLACK;
		}
	}
		alloc.deallocate(result,1);
}
template<class K,class E>
void Rb_map<K,E>::remove_helper(rb_node<K,E>* node,rb_node<K,E>* parent,bool side){
	rb_node<K,E>* sib=side==LEFT?parent->right:parent->left;
	if(!is_black(sib)){
		parent->color=RED;
		sib->color=BLACK;
		if(side==LEFT)
			left_rotation(parent);
		else 
			right_rotation(parent);
		remove_helper(node,parent,side);
		return;
	}
	if(is_black(sib)&&is_black(sib->left)&&is_black(sib->right)){
		sib->color=RED;
		if(!is_black(parent)){
			parent->color=BLACK;
			return;
		}else{
			if(parent->parent->left==parent) side=LEFT;
			else{
				side=RIGHT;
			}
			remove_helper(parent,parent->parent,side);
		}
		return;
	}
	if(is_black(sib)&&(!is_black(sib->left))&&is_black(sib->right)&&side==LEFT){
		sib->color=RED;
		sib->left->color=BLACK;
		right_rotation(sib);
		remove_helper(node,parent,side);
		return;
	}
	if(is_black(sib)&&(!is_black(sib->right))&&is_black(sib->left)&&side==RIGHT){
		sib->color=RED;
		sib->right->color=BLACK;
		left_rotation(sib);
		remove_helper(node,parent,side);
		return;
	}
	if(is_black(sib)&&(!is_black(sib->right))&&side==LEFT){
		bool temp_color=parent->color;
		parent->color=sib->color;
		sib->color=temp_color;
		sib->right->color=BLACK;
		left_rotation(parent);
		return;
	}
	if(is_black(sib)&&(!is_black(sib->left))&&side==RIGHT){
		bool temp_color=parent->color;
		parent->color=sib->color;
		sib->color=temp_color;
		sib->left->color=BLACK;
		right_rotation(parent);
		return;
	}
	
}
#endif 
