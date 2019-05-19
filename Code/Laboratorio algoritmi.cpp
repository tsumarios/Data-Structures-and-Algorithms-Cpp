/*
Argomenti Laboratorio Algoritmi							©ZMDevJockey
*/


#include <iostream>

using namespace std;


/************************************
COUNTING SORT
************************************/
void CountingSort(int *A, int n)
{
	int max = A[0];
	int min = A[0];
	for(int i = 1; i < n; i++)
	{
		if(max < A[i]) max = A[i];
		if(min > A[i]) min = A[i];
	}

	int range = max-min+1;
	int *C = new int[range];
	for(int i = 0; i <= range; i++) C[i] = 0;
	for(int i = 0; i < n; i++) C[A[i]-min]++;

	int j = 0, int k = 0;
	while(j < n)
	{
		while(C[k] > 0)
		{
			A[j++] = k+min;
			C[k]--;
		}
		k++;	
	}
}


/************************************
HEAPS
************************************/
template <class T> class PriorityQueue {
	public:
		virtual T* extract() = 0;
		virtual PriorityQueue<T>* enqueue(T x) = 0;
		virtual int size() = 0;
};

template <class H> class BinaryHeap : public PriorityQueue<H>{
	private:
		H **A;
		int heapsize;
		int len;
		int left(int i) { return i<<1; }
		int right(int i) { return (i<<1)|1; }
		int parent(int i) { return i>>1; }
		
		void scambia(int i, int j) {
			H* tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
		
		void heapify(int i) {
			if(i>heapsize) return;
			int l = left(i);
			int r = right(i);
			int v = i;
			if(l<=heapsize && compare(A[v], A[l])<0) v=l;
			if(r<=heapsize && compare(A[v], A[r])<0) v=r;
			if(v==i) return;
			scambia(i,v);
			heapify(v);
		}
		
		
	public:
		virtual int compare(H *a, H *b)=0;
		BinaryHeap(int size) {
			A = new H*[size];
			len = size;
			heapsize = 0;
		}

		BinaryHeap(H** V, int size) {
			A = V;
			len = size+1;
			heapsize = size;
		}
		
		void buildHeap() {
			for(int i=heapsize/2; i>0; i--)
				heapify(i);
		}

		H* extract() {
			if(heapsize==0) return NULL;
			scambia(1, heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}

		void modify(int i, H k) {
			if(i<1 || i>heapsize) return;
			if( compare(A[i],&k)>=0 ) return;
			A[i] = new H(k);
			while(i>1 && compare(A[i],A[parent(i)])>0) {
				scambia(i,parent(i));
				i = parent(i);
			}
			return;
		}
		
		BinaryHeap<H>* enqueue(H x) {
			if(heapsize==len-1) return this;
			heapsize += 1;
			A[heapsize] = new H(x);
			int i = heapsize;
			while(i>1 && compare(A[i],A[parent(i)])>0) {
				scambia(i, parent(i));
				i = parent(i);
			}
			return this;
		}
		
		void sort() {
			buildHeap();
			int n = heapsize;
			for(int i=0; i<n; i++) extract();
			heapsize = n;
		}
						
		int size() {
			return heapsize;
		}
		
		void print() {
			for(int i=1; i<=heapsize; i++) 
				cout << *A[i] << " ";
			cout << endl;
		}
};

template <class H> class MaxBinaryHeap : public BinaryHeap<H> {
	private: 
	public:
		H compare(H* a, H *b) {
			return (*a)-(*b);
		}
		MaxBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MaxBinaryHeap(H **A, int size) : BinaryHeap<H>(A, size) {}
		H* extractMax() { return BinaryHeap<H>::extract(); }
		void increaseKey(int i, H k) { return BinaryHeap<H>::modify(i,k); }
};

template <class H> class MinBinaryHeap : public BinaryHeap<H> {
	private: 
	public:
		H compare(H* a, H *b) {
			return (*b)-(*a);
		}
		MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MinBinaryHeap(H **A, int size) : BinaryHeap<H>(A, size) {}
		H* extractMin() { return BinaryHeap<H>::extract(); }
		void decreaseKey(int i, H k) { return BinaryHeap<H>::modify(i,k); }
};


/************************************
HASH TABLES
************************************/
template <class T> class HashTable {
	public:
		virtual HashTable<T>* insert(T x) = 0;
		virtual int search(T x) = 0;
		virtual HashTable<T>* del(T x) = 0;
};

template <class H> class LinkedHashTable : public HashTable<H> {
	private:
		virtual int hash(H x) = 0;
		int m;
		int size;
		LinkedList<H> **t;
		
	public:
		LinkedHashTable<H>(int m) {
			t = new LinkedList<H>*[m];
			for(int i=0; i<m; i++) t[i] = new LinkedList<H>();
			this->size = 0;
			this->m = m;
		}
		
		int getm() {return m;}
		void setm(int m) {this->m = m;}
		int getSize() {return size;}
		//void setSize(int size) {this->size = size;}
		
		LinkedHashTable<H>* insert(H x) {
			int p = hash(x);
			t[p]->insert(x);
			size++;
			return this;
		}
		
		int search(H x) {
			int p = hash(x);
			return t[p]->search(x);
		}
		
		LinkedHashTable<H>* del(H x) {
			int p = hash(x);
			if(t[p]->search(x)) {
				t[p]->del(x);
				size--;
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<m; i++) {
				cout << "[" << i << "] -> ";
				t[i]->print();
				cout << endl;
			}
			cout << endl;
		}
};


template <class H> class DivLinkedHashTable : public LinkedHashTable<H> {
	private:
		int hash(H x) {
			int h = ((int)x % this->getm());
			return h;
		}
	public:
		DivLinkedHashTable(int m) : LinkedHashTable<H>(m) {}
};

template <class H> class MulLinkedHashTable : public LinkedHashTable<H> {
	private:
		double c;
		int hash(H x) {
			double y = (int)x * c;
			double a = y - (int)y; 
			int h = a * this->getm();
			return h;
		}
	public:
		MulLinkedHashTable(int m) : LinkedHashTable<H>(m) {
			c = 0.7;
		}
};


template <class H> class OpenHashTable : public HashTable<H> {
	private:
		virtual int hash(H x, int i) = 0;
		int m;
		int size;
		H **t;
		H *deleted;
		
	public:
		OpenHashTable<H>(int m) {
			t = new H*[m];
			for(int i=0; i<m; i++) t[i] = NULL;
			this->size = 0;
			this->m = m;
			deleted = new H();
		}
		
		int getm() {return m;}
		void setm(int m) {this->m = m;}
		int getSize() {return size;}
		
		OpenHashTable<H>* insert(H x) {
			if(size==m) return this;
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL && t[p]!=deleted) {
				i++;
				p = hash(x,i);
			}
			if(t[p]==NULL || t[p]==deleted) t[p] = new H(x);
			return this;
		}
		
		int search(H x) {
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL) {
				if( t[p]!=deleted && *t[p]==x ) return 1;
				i++;
				p = hash(x,i);
			}
			return 0;
		}
		
		OpenHashTable<H>* del(H x) {
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL) {
				if( *t[p]==x ) {
					t[p] = deleted;
					return this;
				}
				i++;
				p = hash(x,i);
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<m; i++) {
				if(t[i] && t[i]!=deleted) cout << "[" << i << "] -> " << *t[i];
				else cout << "[" << i << "] -> //";
				cout << endl;
			}
			cout << endl;
		}
};

template <class H> class LinearOpenHashTable : public OpenHashTable<H> {
	private:
		int hash(H x, int i) {
			return (((int)x % this->getm()) + i) % this->getm();
		}
	public:
		LinearOpenHashTable(int m) : OpenHashTable<H>(m) {
		}
};


/************************************
RED-BLACK TREE
************************************/
template <class H> class RBTree : public BSTree<H> {
	private:
		static const int BLACK = 0;
		static const int RED = 1;
		static const int BLACKBLACK = 2;

		void inorder_visit(Node<H>* n) {
			if(n!=NULL) {
				inorder_visit(n->getLeft());
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
				inorder_visit(n->getRight());
			}
		}

		void postorder_visit(Node<H>* n) {
			if(n!=NULL) {
				postorder_visit(n->getLeft());
				postorder_visit(n->getRight());
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
			}
		}

		void preorder_visit(Node<H>* n) {
			if(n!=NULL) {
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
				preorder_visit(n->getLeft());
				preorder_visit(n->getRight());
			}
		}
		
		char printC(int color) {
			if(color==0) return 'B';
			if(color==1) return 'R';
			return 'X';
		}
		
		void RBInsertFixup(Node<H> *z) {
			if(z->getParent()!=NULL && z->getParent()->getColor()==BLACK) return;
			if(z == this->getRoot()) {
				z->setColor(BLACK);
				return;
			}
			Node<H> *padre = z->getParent();
			Node<H> *nonno = padre->getParent();
			Node<H> *zio = nonno->getRight();
			if(padre == nonno->getRight()) zio = nonno->getLeft();
			if(zio!=NULL && zio->getColor() == RED) {
				// caso 1
				zio->setColor(BLACK);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				RBInsertFixup(nonno);
				return;
			}
			if(padre == nonno->getLeft()) {
				if(z == padre->getRight()) {
					// caso 3
					this->leftRotate(padre);
					padre = z;
					z = padre->getLeft();
				}
				// caso 2
				this->rightRotate(nonno);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				return;
			}
			else { // casi simmetrici ai precedenti
				if(z == padre->getLeft()) {
					// caso 3
					this->rightRotate(padre);
					padre = z;
					z = padre->getRight();
				}
				// caso 2
				padre->setColor(BLACK);
				nonno->setColor(RED);
				this->leftRotate(nonno);
				return;
			}
		}
		
		void swapColor(Node<H> *x, Node<H> *y) {
			int tmp = x->getColor();
			x->setColor(y->getColor());
			y->setColor(tmp);
		}

			
	public:
		RBTree<H>() : BSTree<H>() {}
		RBTree<H> *insert(H key) {
			BSTree<H>::insert(key);
			Node<H> *n = this->search(key);
			n->setColor(RED);
			RBInsertFixup(n);
			return this;
		}
		
		void inorder() { inorder_visit(this->getRoot()); cout << endl; }
		void postorder() { postorder_visit(this->getRoot()); cout << endl; }
		void preorder() { preorder_visit(this->getRoot()); cout << endl; }
};

int main()
{
	cin.get();
	return 0;
}
