/*
Hash Tables							©ZMDevJockey
*/

#include <iostream>
#include "List.cpp"

using namespace std;


/*********************************** HASH TABLES ***********************************/

/*********************************** Linked Hash ***********************************/

/**************************
Class LinkedHashTable
**************************/
template<class H> class LinkedHashTable
{
		virtual int hash(H x) = 0;

		int m, size;
		LinkedList<H> **t;

	public:
		LinkedHashTable(int m)
		{
			t = new LinkedList<H>*[m];
			for(int i = 0; i < m; i++)	t[i] = new LinkedList<H>();
			size = 0;
			this->m = m;
		}

		int getM() { return m; }
		void setM(int m) { this->m = m; }
		int getSize() { return size; }

		LinkedHashTable<H>* ins(H x)
		{
			int p = hash(x);
			t[p]->insert(x);
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
				t[p]->del(x);
				size--;
			}
			return this;
		}

		void print()
		{
			for(int i = 0; i < m; i++)
			{
				cout << "[" << i << "] -> ";
				t[i]->print();
				cout << endl;
			}
			cout << endl;
		}
};


/**************************
Class DivLinkedHashTable
**************************/
template<class H> class DivLinkedHashTable : public LinkedHashTable<H>
{
		int hash(H x)
		{
			int h = ((int)x % this->getM());
			return h;
		}

	public:
		DivLinkedHashTable(int m) : LinkedHashTable<H>(m) {}

};


/**************************
Class MulLinkedHashTable
**************************/
template<class H> class MulLinkedHashTable : public LinkedHashTable<H>
{
		double c;

		int hash(H x)
		{
			double y = int(x) * c;
			double a = y - int(y);
			int h = a * this->getM();
			return h;
		}

	public:
		MulLinkedHashTable(int m) : LinkedHashTable<H>(m) { c = 0.7; }
};


/*********************************** Open Hash ***********************************/

/**************************
Class OpenHashTable
**************************/
template<class H> class OpenHashTable
{
		virtual int hash(H x, int i) = 0;

		int m, size;

		H **t;
		H *deleted;

	public:
		OpenHashTable(int m)
		{
			t = new H*[m];
			for(int i = 0; i < m; i++)	t[i] = NULL;
			size = 0;
			this->m = m;
			deleted = new H();
		}

		int getM() { return m; }
		void setM(int m) { this->m = m;}
		int getSize() { return size; }

		OpenHashTable<H>* ins(H x)
		{
			if(size == m) return this;

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
				if(t[i] && t[i] != deleted)	cout << "[" << i << "] ->" << *t[i];
				else cout << "[" << i << "] -> //";
				cout << endl;
			}
			cout << endl;
		}

};


/**************************
Class LinearOpenHashTable
**************************/
template<class H> class LinearOpenHashTable : public OpenHashTable<H>
{
		int hash(H x, int i)
		{
			return (((int)x % this->getM()) + i ) % this->getM();
		}

	public:
		LinearOpenHashTable(int m) : OpenHashTable<H>(m) {}

};


/*********************************** Main ***********************************/
int main()
{
	DivLinkedHashTable<int> *d = new DivLinkedHashTable<int>(5);
	d->ins(3)->ins(5)->ins(10)->ins(24)->ins(33)->ins(77);
	d->del(4)->del(5);
	d->ins(5);
	d->print();

	LinearOpenHashTable<int> *m = new LinearOpenHashTable<int>(11);
	m->ins(4)->ins(34)->ins(31)->ins(56)->ins(51)->ins(44)->ins(33)->ins(77)->ins(50);
	m->del(34)->del(77);
	m->ins(77)->ins(22);
	m->print();
	

	cin.get();
	return 0;
}
