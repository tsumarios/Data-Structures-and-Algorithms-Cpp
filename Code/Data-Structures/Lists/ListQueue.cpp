/* Coded by ©ZMDevJockey */

/*
ListQueue Template
*/

#include <iostream>

using namespace std;

/******************* Class Node *******************/
template<class H> class Node
{
    H *key;
    Node<H> *prev, *next;

  public:
    Node(H *key = NULL, Node<H> *prev = NULL, Node<H> *next = NULL)
    {
      if(key)   this->key = new H(*key);
      else      this->key = NULL;
      this->prev = prev;
      this->next = next;
    }

    void setPrev(Node<H> *prev) { this->prev = prev; }
    void setNext(Node<H> *next) { this->next = next; }
    void setKey(H *key) { this->key = new H(*key); }

    Node<H>* getPrev() { return prev; }
    Node<H>* getNext() { return next; }
    H* getKey() { return new H(*key); }
};


/******************* Class LinkedList *******************/
template<class H> class LinkedList
{
		Node<H>* head, *tail;
		int n;

		Node<H>* _search(H x)
		{
			Node<H>* tmp = head;
			while(tmp != NULL) {
				if(*tmp->getKey() == x) return tmp;
				tmp = tmp->getNext();
			}
			return NULL;
		}

	public:
		LinkedList()
		{
			head = tail = NULL;
			n = 0;
		}

		bool isEmpty() { return n==0 ? 1:0; }

		LinkedList<H>* ins(H x)
		{
			Node<H>* nd = new Node<H>(&x);
			nd->setNext(head);
			if(head) head->setPrev(nd);
			head = nd;
			n++;
			if(!tail) tail = nd;
			return this;
		}

		LinkedList<H>* insTail(H x)
		{
			Node<H>* nd = new Node<H>(&x);
			if(tail) tail->setNext(nd);
			else 			head = nd;
			nd->setPrev(tail);
			tail = nd;
			n++;
			return this;
		}

		bool search(H x)
		{
			Node<H>* tmp = head;
			while(tmp != NULL)
			{
				if( tmp->getKey()==x )	return true;
				tmp = tmp->getNext();
			}
			return false;
		}

		LinkedList<H>* del(H x)
		{
			Node<H> *tmp = _search(x);
			if(!tmp) return this;
			Node<H>* p = tmp->getPrev();
			Node<H>* s = tmp->getNext();
			if(p) p->setNext(s);
			else head = s;
			if(s) s->setPrev(p);
			else tail = p;
			n--;
			return this;
		}

		H* getHead()
		{
			if(!head) return NULL;
			H *key = new H(*head->getKey());
			return key;
		}

		void print()
		{
			cout << "[" << n << "] ";
			Node<H> *tmp = head;
			while(tmp !=NULL )
			{
				cout << *tmp->getKey() << " ";
				tmp = tmp->getNext();
			}
			cout << endl;
		}

};


/******************* Class ListQueue *******************/
template<class H> class ListQueue
{
    LinkedList<H> *q;

  public:
    ListQueue()
    {
      q = new LinkedList<H>();
    }

    bool isEmpty() { return q->isEmpty(); }

    int getSize() { return q->getSize(); }

    ListQueue<H>* enqueue(H x)
    {
      q->insTail(x);
      return this;
    }

    H* dequeue()
    {
  			if(q->isEmpty()) return NULL;
  			H* tmp = q->getHead();
  			q->del(*(tmp));
  			return tmp;
  	}

    void print()
    {
      q->print();
    }

};


/******************* Main *******************/
int main()
{
    ListQueue<int> *q = new ListQueue<int>();
    q->enqueue(3)->enqueue(1)->enqueue(7);
    q->print();

    q->dequeue();
    q->print();


    cin.get();
    return 0;
}
ad);
			if(head) head->setPrev(nd);
			head = nd;
			n++;
			if(!tail) tail = nd;
			return this;
		}

		LinkedList<H>* insTail(H x)
		{
			Node<H>* nd = new Node<H>(&x);
			if(tail) tail->setNext(nd);
			else 			head = nd;
			nd->setPrev(tail);
			tail = nd;
			n++;
			return this;
		}

		bool search(H x)
		{
			Node<H>* tmp = head;
			while(tmp != NULL)
			{
				if( tmp->getKey()==x )	return true;
				tmp = tmp->getNext();
			}
			return false;
		}

		LinkedList<H>* del(H x)
		{
			Node<H> *tmp = _search(x);
			if(!tmp) return this;
			Node<H>* p = tmp->getPrev();
			Node<H>* s = tmp->getNext();
			if(p) p->setNext(s);
			else head = s;
			if(s) s->setPrev(p);
			else tail = p;
			n--;
			return this;
		}

		H* getHead()
		{
			if(!head) return NULL;
			H *key = new H(*head->getKey());
			return key;
		}

		void print()
		{
			cout << "[" << n << "] ";
			Node<H> *tmp = head;
			while(tmp !=NULL )
			{
				cout << *tmp->getKey() << " ";
				tmp = tmp->getNext();
			}
			cout << endl;
		}

};


/******************* Class ListQueue *******************/
template<class H> class ListQueue
{
    LinkedList<H> *q;

  public:
    ListQueue()
    {
      q = new LinkedList<H>();
    }

    bool isEmpty() { return q->isEmpty(); }

    int getSize() { return q->getSize(); }

    ListQueue<H>* enqueue(H x)
    {
      q->insTail(x);
      return this;
    }

    H* dequeue()
    {
  			if(q->isEmpty()) return NULL;
  			H* tmp = q->getHead();
  			q->del(*(tmp));
  			return tmp;
  	}

    void print()
    {
      q->print();
    }

};


/******************* Main *******************/
int main()
{
    ListQueue<int> *q = new ListQueue<int>();
    q->enqueue(3)->enqueue(1)->enqueue(7);
    q->print();

    q->dequeue();
    q->print();


    cin.get();
    return 0;
}
