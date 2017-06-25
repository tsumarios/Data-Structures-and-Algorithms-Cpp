/*
 * Programmazione 2
 * Esame 23 giugno 2017 - Compito B
 * Coded by ©ZMDevJockey
 */

#include <iostream>

using namespace std;


/* Esercizio 1 */

/*******************
Class Studente
*******************/
class Studente{
	string matr;
	int v, r, e;

public:
	Studente(string m, int vi, int ri, int ei): matr(m), v(vi), r(ri), e(ei) {}

	void setVoto(int v)	{ this->v = v; }
	void setRisp(int r)	{ this->r = r; }
	void setEta(int e)	{ this->e = e; }

	int getVoto()	{ return v; }
	int getRisp()	{ return r; }
	int getEta()	{ return e; }
	string getMatr()	{ return matr; }
};

/* Overloadings */
bool operator>(Studente &a, Studente &b)	{ return (a.getVoto()<b.getVoto()) || (a.getVoto()==b.getVoto() && a.getRisp()<b.getRisp()) || (a.getVoto()==b.getVoto() && a.getRisp()==b.getRisp() && a.getEta()>b.getEta()); }
bool operator<(Studente &a, Studente &b)	{ return a>b ? 0:1; }
bool operator==(Studente &a, Studente &b)	{ return a.getVoto()==b.getVoto() && a.getRisp()==b.getRisp() && a.getEta()==b.getEta(); }
bool operator!=(Studente &a, Studente &b)	{ return a==b ? 0:1; }
bool operator>=(Studente &a, Studente &b)	{ return a>b || a==b; }
bool operator<=(Studente &a, Studente &b)	{ return a<b || a==b; }
ostream &operator<<(ostream &os, Studente s)	{ return os << s.getMatr(); }


/* Esercizio 2 */

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

	Node<H>* getLeft()	{ return left; }
	Node<H>* getRight()	{ return right; }
	Node<H>* getParent()	{ return parent; }
	H* getKey()	{ return new H(*key); }
};

/*******************
Class BST
*******************/
template<class H> class BST{
	int n;
	Node<H> *root, *current;

	//Ritorna il nodo a partire dalla sua chiave
	Node<H>* _searchNode(H e){
		if(!root)	return NULL;
		Node<H> *x = root;
		while(x && *x->getKey() != e){
			if(e < *x->getKey())	x = x->getLeft();
			else	x = x->getRight();
		}
		return x;
	}

	//Stampa ricorsiva in-order
	void _print(Node<H> *tmp){
		if(!tmp)	return;
		_print(tmp->getLeft());
		cout << *tmp->getKey() << " ";
		_print(tmp->getRight());
	}

public:
	BST(): n(0), root(NULL) {}

	//Inserisce un nuovo nodo
	BST<H>* ins(H x){
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

	bool search(H x)	{ return _searchNode(x); }

	void print()	{ _print(root);	cout << endl; }
};


/* Esercizio 3 */

/*******************
Class BSTS
*******************/
template<class H>class BSTS : public BST<H>{
	int n;
	Node<H> *root, *current;

	//Trova il nodo più piccolo partendo da quello in input
	Node<H>* _minimum(Node<H> *tmp){
		if(!tmp)	return NULL;
		Node<H> *x = tmp;
		while(x->getLeft())	x = x->getLeft();
		return x;
	}

	//Trova il nodo successivo a quello in input
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

public:
	BSTS() { BST<H>(); }

	//Necessario includere nell'inserimento il controllo di univocità delle matricole
	BST<H>* ins(H x){
		Node<H> *nd = new Node<H>(&x);
		if(!root){
			root = nd;
			n++;
			return this;
		}
		if(!checkUniq(nd->getKey())) { delete(nd); return this; }	//Non può esistere uno studente con matricola identica ad un altro
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
	
	//Ritorna il p-esimo oggetto di tipo H
	H searchS(int p){
		H *it = begin();
		for(int i = 1; it && i < p; i++) it = next();
		return *it;
	}

	//Iteratore
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

	//Restituisce falso se esiste già uno studente con la stessa matricola
	bool checkUniq(H *tmp){
		for(H *it = begin(); it; it = next())	if(it->getMatr() == tmp->getMatr())	return false;
		return true;	
	}

	void print()	{ for(H *it = begin(); it; it = next())	cout << *it << " "; }
};

/*******************
Class Valutazione
*******************/
class Valutazione{
	int n;
	BSTS<Studente> *t;

public:
	Valutazione(): n(0), t(new BSTS<Studente>())	{ t->begin(); }

	Valutazione* ins(Studente s)	{ t->ins(s); return this; }

	//Ritorna il p-esimo studente nella posizione della valutazione
	Studente search(int p)	{ return t->searchS(p); }

	void print()	{ t->print(); }
};


/*******************
Main
*******************/
int main(){
	/* Esercizio 1 */
	int voto = 89, r = 60, e = 27;
	Studente *a = new Studente("X81000123", voto, r, e);
	Studente *b = new Studente("X81000452", 63, 63, 24);
	Studente *c = new Studente("X81000104", 89, 60, 25);
	if(*a < *b)	cout << "True";	else cout << "False"; cout << endl;
	if(*a >= *b)	cout << "True";	else cout << "False"; cout << endl;
	if(*a == *c)	cout << "True";	else cout << "False"; cout << endl;
	if(*a <= *c)	cout << "True";	else cout << "False"; cout << endl;

	/* Esercizio 2 */
	BST<int> *t = new BST<int>();
	t->ins(2)->ins(3)->ins(12)->ins(4)->ins(9)->ins(5);
	t->print();
	
	/* Esercizio 3 */
	Valutazione *v = new Valutazione();
	v->ins(*a)->ins(*b)->ins(*c);	
	cout << v->search(2) << endl;
	v->print();


	cin.get();
	return 0;
}
