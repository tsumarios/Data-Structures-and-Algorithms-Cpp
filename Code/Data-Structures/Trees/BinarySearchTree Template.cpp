/*
 * Binary Search Tree with Template
 * Coded by ©ZMDevJockey
 */

#include <iostream>

using namespace std;


/*******************
Class Node
*******************/
template<class H> class Node{
	H *key;
	Node<H> *left, *right, *parent;

public:
	Node(H *key, Node<H> *left = NULL, Node<H> *right = NULL, Node<H> *parent = NULL){
		if(key)	this->key = new H(*key);	//difensive copy
		else	this->key = NULL;
		this->left = left;
		this->right = right;
		this->parent = parent;
	}

	void setLeft(Node<H> *left)	{ this->left = left; }
	void setRight(Node<H> *right)	{ this->right = right; }
	void setPar(Node<H> *parent)	{ this->parent = parent; }
	void setKey(H *key)	{ this->key = new H(*key); }

	Node<H>* getLeft() { return left; }
	Node<H>* getRight() { return right; }
	Node<H>* getParent() { return parent; }
	H* getKey()	{ return new H(*key); }
};


/*******************
Class BSTree
*******************/
template<class H> class BSTree{
	int n;
	Node<H> *root, *current;

	Node<H>* _searchNode(H e){
		if(!root)	return NULL;
		Node<H> *x = root;
		while(x && *x->getKey() != e){
			if(e < *x->getKey())	x = x->getLeft();
			else	x = x->getRight();
		}
		return x;
	}

	Node<H>* _minimum(Node<H> *tmp){
		if(!tmp)	return NULL;
		Node<H> *x = tmp;
		while(x->getLeft())	x = x->getLeft();
		return x;
	}

	Node<H>* _succ(Node<H> *tmp){
		if(!tmp)	return NULL;
		if(tmp->getRight())	return _minimum(tmp->getRight());
		Node<H> *x = tmp;
		Node<H> *y = tmp->getParent();
		while(y && y->getRight() == x){
			x = y;
			y = y->getParent();
		}
		return y;
	}

	BSTree<H>* _del(Node<H> *tmp){
		if(!tmp)	return this;

		/* First case: tmp hasn't children */
		if(!tmp->getLeft() && !tmp->getRight()){
			Node<H> *y = tmp->getParent();
			if(!y)	root = NULL;
			else	
				if(y->getLeft() == tmp)	y->setLeft(NULL);
				else	y->setRight(NULL);
			delete(tmp);
			n--;
			return this;
		}

		/* Third case: tmp has both children */
		if(tmp->getLeft() && tmp->getRight()){
			Node<H> *s = _succ(tmp);
			tmp->setKey(s->getKey());
			_del(s);
			return this;
		}

		/* Second case: tmp has only one child */
		Node<H> *y = tmp->getParent();
		Node<H> *z = tmp->getLeft();
		if(!z)	z = tmp->getRight();
		if(!y)	root = z;
		else
			if(y->getLeft() == tmp)	y->setLeft(z);
			else y->setRight(z);
		z->setPar(y);
		delete(tmp);
		n--;
		return this;
	}

	void _preOrder(Node<H> *tmp){
		if(!tmp)	return;
		cout << *tmp->getKey() << " ";
		_preOrder(tmp->getLeft());
		_preOrder(tmp->getRight());
	}

	void _postOrder(Node<H> *tmp){
		if(!tmp)	return;
		_postOrder(tmp->getLeft());
		_postOrder(tmp->getRight());
		cout << *tmp->getKey() << " ";
	}

public:
	BSTree(): n(0), root(NULL) {}

	BSTree<H>* ins(H x){
		Node<H> *nd = new Node<H>(&x);
		if(!root){
			root = nd;
			n++;
			return this;
		}
		Node<H> *tmp = root;
		Node<H> *par = NULL;
		while(tmp){
			par = tmp;
			if(x < *tmp->getKey())	tmp = tmp->getLeft();
			else	tmp = tmp->getRight();
		}
		if(x < *par->getKey())	par->setLeft(nd);
		else	par->setRight(nd);
		nd->setPar(par);
		n++;
		return this;
	}

	BSTree<H>* del(H x){
		Node<H> *tmp = _searchNode(x);
		if(tmp)	_del(tmp);
		return this;
	}

	bool search(H x)	{ return _searchNode(x); }

	H* begin(){
		current = _minimum(root);
		if(current)	return current->getKey();
		return NULL;
	}

	H* next(){
		if(current)	current = _succ(current);
		if(current)	return current->getKey();
		return NULL;
	}

	void print(){
		for(H *it = begin(); it; it = next())	cout << *it << " ";
		cout << endl;
	}

	void printPre(){
		_preOrder(root);
		cout << endl;
	}

	void printPost(){
		_postOrder(root);
		cout << endl;
	}

};

//Overloading << operator
template<class H> ostream &operator<<(ostream &os, BSTree<H> &obj){
	for(H *it = obj.begin(); it; it = obj.next())	os << *it << " ";
	return os << endl;
}

/*******************
Main
*******************/
int main(){

	BSTree<int> *t = new BSTree<int>();
	t->ins(1)->ins(3)->ins(7)->ins(2)->ins(8);
	cout << *t;
	t->print();
	t->printPre();
	t->printPost();

	cout << endl;

	t->del(1)->del(8);
	cout << *t;
	t->print();
	t->printPre();
	t->printPost();

	cin.get();
	return 0;
}
