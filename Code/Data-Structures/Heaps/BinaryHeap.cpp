#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

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
		int compare(H* a, H *b) {
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
		int compare(H* a, H *b) {
			return (*b)-(*a);
		}
		MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MinBinaryHeap(H **A, int size) : BinaryHeap<H>(A, size) {}
		H* extractMin() { return BinaryHeap<H>::extract(); }
		void decreaseKey(int i, H k) { return BinaryHeap<H>::modify(i,k); }
};

int main() {	
	/*MaxBinaryHeap<int> *B = new MaxBinaryHeap<int>(100);
	B->enqueue(6)->enqueue(9)->enqueue(2)->enqueue(7)->enqueue(12);
	B->extractMax();
	B->enqueue(4)->enqueue(1)->enqueue(5);
	B->increaseKey(6,8);
	B->increaseKey(5,14);
	B->extractMax();
	B->print();*/
	
	int n = 100;
	int **V = new int*[n+1];
	for(int i=1; i<=n; i++) V[i] = new int(rand() % 100);
	MinBinaryHeap<int> *B = new MinBinaryHeap<int>(V,n);
	B->print();
	B->sort();
	B->print();
	return 1;
}
