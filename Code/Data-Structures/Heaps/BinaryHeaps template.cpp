/*
Binary Heaps							©ZMDevJockey
*/

#include <iostream>

using namespace std;


/*********************************** Binary Heap ***********************************/

/**************************
Class BinaryHeap
**************************/
template<class H> class BinaryHeap
{
		H **A;
		int heapsize, len;

		int left(int i)	{ return i<<1; }
		int right(int i)	{ return (i<<1) | 1; }
		int parent(int i)	{ return i>>1; }
	
		void swap(int i, int j)
		{
			H *tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}

		void heapify(int i)
		{
			if(i > heapsize) return;

			int l = left(i);
			int r = right(i);
			int v = i;
			if(l <= heapsize && compare(A[v], A[l]) < 0) v = l;
			if(r <= heapsize && compare(A[v], A[r]) < 0) v = r;
			if(v == i)	return;
			swap(i,v);
			heapify(v);
		}

	public:
		virtual H compare(H *a, H *b) = 0;			//Assumendo che vi sia l'overloading dell'operatore - per il tipo H

		BinaryHeap(int size)
		{
			A = new H*[size];
			len = size;
			heapsize = 0;
		}

		BinaryHeap(H **V, int size)
		{
			A = V;
			len = size;
			heapsize = size;
		}

		void buildHeap()
		{
			for(int i = heapsize/2; i > 0; i--)
				heapify(i);
		}

		H* extract()
		{
			if(heapsize == 0)	return NULL;

			swap(1,heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}

		BinaryHeap<H>* enqueue(H x)
		{
			if(heapsize == len) return this;

			heapsize++;
			A[heapsize] = new H(x);
			int i = heapsize;
			while(i > 1 && compare(A[i], A[parent(i)]) > 0)
			{
				swap(i,parent(i));
				i = parent(i);
			}
			return this;
		}

		void sort()
		{
			buildHeap();
			int n = heapsize;
			for(int i = 0; i < n; i++)	extract();
			heapsize = n;
		}

		int getSize() { return heapsize; }

		void print()
		{
			for(int i = 1; i <= heapsize; i++)
			
				cout << *A[i] << " ";
			cout << endl;
		}

};

/**************************
Class MaxBinaryHeap
**************************/
template<class H> class MaxBinaryHeap : public BinaryHeap<H>
{
	public:
		H compare(H *a, H *b) { return (*a)-(*b); }

		MaxBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MaxBinaryHeap(H **V, int size) : BinaryHeap<H>(V,size) {}

		H* extractMax() { return BinaryHeap<H>::extract(); }
};

/**************************
Class MinBinaryHeap
**************************/
template<class H> class MinBinaryHeap : public BinaryHeap<H>
{
	public:
		H compare(H *a, H *b)	{ return (*b)-(*a); }

		MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MinBinaryHeap(H **V, int size) : BinaryHeap<H>(V,size) {}

		H* extractMin() { return BinaryHeap<H>::extract(); }
};


/*********************************** Main ***********************************/
int main()
{
	MaxBinaryHeap<int> *maxH = new MaxBinaryHeap<int>(10);
	maxH->enqueue(6)->enqueue(9)->enqueue(2)->enqueue(7)->enqueue(12);
	maxH->extractMax();
	maxH->enqueue(4)->enqueue(1)->enqueue(5);
	maxH->extractMax();
	maxH->print();

	cout << endl;

	int n = 10;
	int **V = new int*[n+1];
	for(int i = 1; i <= n; i++) V[i] = new int(rand() % 10);
	MinBinaryHeap<int> *minH = new MinBinaryHeap<int>(V,n);
	minH->print();
	minH->buildHeap();
	minH->print();
	
	cout << endl;

	cin.get();
	return 0;
}
