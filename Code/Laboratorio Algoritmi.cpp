/*
Coded by ©ZMDevJockey
*/


/**************************************
Counting Sort
**************************************/
void countingSort(int *A, int n)
{
	int max = A[0];
	int min = A[0];
	for(int i = 0; i < n; i++)
	{
		if(max < A[i])	max = A[i];
		if(min > A[i])	min = A[i];
	}

	int range = max-min+1;
	int *C = new int[range];
	for(int i = 0; i <= range; i++)	C[i] = 0;
	for(int i = 0; i < range; i++)	C[A[i]-min]++;

	int j = 0; k = 0;
	while(j < n)
	{
		while(C[k] > 0)
		{
			C[j++] = k+min;
			C[k]--;
		}
		k++;
	}
}


/************************************ START HEAPS ************************************/

/**************************************
Binary Heap
**************************************/
template<class H> class BinaryHeap : public PriorityQueue<H>
{
		H **A;
		int heapsize, len;

		int left(int i)	{ return i<<1; }
		int right(int i) { return (i<<1) || 1; }
		int parent(int i) { return i>>1; }

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
			if(l <= heapsize && compare(A[v], A[l]) < 0)	v = l;
			if(r <= heapsize && compare(A[v], A[r]) < 0)	v = r;
			if(v == i)	return;
			swap(i,v);
			heapify(v);
		}

	public:
		virtual int compare(H *a, H *b) = 0;

		BinaryHeap(int size)
		{
			A = new H*[size];
			len = size+1;
			heapsize = size;
		}

		BinaryHeap(H ** V, int size)
		{
			A = V;
			len = size+1;
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

			swap(1, heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}

		void sort()
		{
			buildHeap();
			int n = heapsize;
			for(int i = 0; i < n; i++)	extract();
			heapsize = n;
		}
		
};

/**************************************
Max Binary Heap
**************************************/
template<class H> class MaxBinaryHeap : public BinaryHeap<H>
{
	public:
		int compare(H *a, H *b)
		{
			return (*a)-(*b);
		}

		MaxBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MaxBinaryHeap(H **V, int size) : BinaryHeap<H>(V, size) {}

		H* extractMax() { return BinaryHeap<H>::extract(); }
};

/**************************************
Min Binary Heap
**************************************/
template<class H> class MinBinaryHeap : public BinaryHeap<H>
{
	public:
		int compare(H *a, H *b)
		{
			return (*b)-(*a);
		}

		MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
		MinBinaryHeap(H **V, int size) : BinaryHeap<H>(V, size) {}

		H* extractMin() { return BinaryHeap<H>::extract(); }
};

/************************************ END HEAPs ************************************/



/************************************ START HASH TABLES ************************************/

/**************************************
Linked Hash Table
**************************************/
template<class H> class LinkedHashTable : public HashTable<H>
{
		virtual int hash(H x) = 0;

		int m, size;
		LinkedList<H> **t;

	public:
		LinkedHashTable(int m)
		{
			t = new LinkedList<H>*[m];
			for(int i = 0; i < m; i++)	t[i] = new LinkedList<H>();
			this->m = m;
			this->size = 0;
		}

		int getM()	{ return m; }
		void setM(int m) { this->m = m; }
		int getSize() { return size;}

		LinkedHashTable<H>* ins(H x)
		{
			int p = hash(x);
			t[p]->ins(x);
			size++;
			return this;
		}

		bool search(H x)
		{
			int p = hash(x);
			return t[p]->search(x);
		}

		LinkedHashTable<H>* del(H x)
		{
			int p = hash(x);
			if(t[p]->search(x))
			{
				t[p]->del();
				size--;
			}
			return this;
		}

		void print()
		{
			for(int i = 0; i < m; i++)
			{
				cout << "[" << i << "]" << endl;
				t[i]->print();
				cout << endl;
			}
			cout << endl;
		}

};

/**************************************
Div Linked Hash Table
**************************************/
template<class H> class DivLinkedHashTable : public LinkedHashTable<H>
{
		int hash(H x)
		{
			int h = (int(x) % this->getM());
			return h;
		}

	public:
		DivLinkedHashTable(int m) : LinkedHashTable<H>(m) {}
};

/**************************************
Mul Linked Hash Table
**************************************/
template<class H> class MulLinkedHashTable : public LinkedHashTable<H>
{
		double c;

		int hash(H x)
		{
			double y = int(x) * c;
			double a = y - (int)y;
			int h = a * this->getM();
			return h;
		}

	public:
		MulLinkedHashTable(int m) : LinkedHashTable<H>(m) { c = 0.7; }

};

/**************************************
Open Hash Table
**************************************/
template<class H> class OpenHashTable : public HashTable<H>
{
		virtual hash(H x, int i) = 0;

		int m, size;
		H **t;
		H *deleted;

	public:
		OpenHashTable(int m)
		{
			t = new H*[m];
			for(int i = 0; i < m; i++)	t[i] = NULL;
			this->m = m;
			size = 0;
			deleted = new H();
		}

		int getM() { return m; }
		void setM(int m) { this->m = m; }
		int getSize() { return size; }

		OpenHashTable<H>* ins(H x)
		{
			if(size == m)	return this;
			int i = 0;
			int p = hash(x,i);
			while(i < m && t[p] && t[p] != deleted)
			{
				i++;
				p = hash(x,i);
			}
			if(!t[p] || t[p] == deleted) t[p] = new H(x);
			return this;
		}

		bool search(H x)
		{
			int i = 0;
			int p = hash(x,i);
			while(i < m && t[p])
			{
				if(t[p] != deleted && *t[p] == x)	return true;
				i++;
				p = hash(x,i);
			}
			return false;
		}

		OpenHashTable<H>* del(H x)
		{
			int i = 0;
			int p = hash(x,i);
			while(i < m && t[p])
			{
				if(*t[p] == x)
				{
					t[p] = deleted;
					return this;
				}
				i++;
				p = hash(x,i);
			}
			return this;
		}

		void print()
		{
			for(int i = 0; i < m; i++)
			{
				if(t[i] && t[i] != deleted)	cout << "[" << i << "] -> " << *t[i];
				else	cout << "[" << i << "] -> //";
				cout << endl;
			}
			cout << endl;
		}
};

/**************************************
Linear Open Hash Table
**************************************/
template<class H> class LinearOpenHashTable : public OpenHashTable<H>
{
		int hash(H x, int i)
		{
			int h = ((int(x) % this->getM()) + i ) % this->getM();
			return h;
		}

	public:
		LinearOpenHashTable(int m) : OpenHashTable<H>(m) {}

};

/************************************ END HASH TABLES ************************************/



/************************************ START RED BLACK TREE ************************************/
template<class H> class RBTree : public BSTree<H>
{
		static const int BLACK = 0;
		static const int RED = 1;
		static const int BLACKBLACK = 2;

		void rbInsertFixUp(Node<H> *z)
		{
			if(z->getParent() && z->getParent()->getColor() == BLACK)	return;
			if(z == this->getRoot())
			{
				z->setColor(BLACK);
				return;
			}

			Node<H> *padre = z->getParent();
			Node<H> *nonno = padre->getParent();
			Node<H> *zio = nonno->getLeft();
			if(padre == nonno->getLeft())	zio = nonno->getRight();

			//Caso zio rosso
			if(zio && zio->getColor == RED)
			{
				zio->setColor(BLACK);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				rbInsertFixUp(nonno);
				return;
			}

			if(padre == nonno->getLeft())
			{
				if(z == padre->getLeft())
				{
					this->leftRotate(padre);
					padre = z;
					z = padre->getLeft();
				}

				this->rightRotate(nonno);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				return;
			}
			else
			{ 
				if(z == padre->getLeft())
				{
					this->rightRotate(padre);
					padre = z;
					z = padre->getRight();
				}
				
				padre->setColor(BLACK);
				nonno->setColor(RED);
				this->leftRotate(nonno);
				return;
			}
		}

	public:
		RBTree() : BSTree<H>() {}

		RBTree<H>* ins(H x)
		{
			BSTree<H>::ins(x);
			Node<H> *n = this->search(x);
			n->setColor(RED);
			rbInsertFixUp(n);
			return this;
		}

};

/************************************ END RED BLACK TREE ************************************/
