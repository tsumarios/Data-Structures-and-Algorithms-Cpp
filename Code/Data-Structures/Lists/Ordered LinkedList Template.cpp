/* Coded by Z Ov3rFlow */

/*
Ordered LinkedList Template
*/

#include <iostream>

using namespace std;

/******************* Class Node *******************/
template<class H> class Node
{
    H *key;
    Node<H> *next;

  public:
    Node(H *key = NULL, Node<H> *next = NULL)
    {
      if(key) this->key = new H(*key);
      else    this->key = NULL;
      this->next = next;
    }

    void setNext(Node<H> *next) { this->next = next; }
    void setKey(Node<H> *key) { this->key = new H(*key); }

    Node<H>* getNext() { return next; }
    H* getKey() { return new H(*key); }
};

/******************* Class LList  *******************/
template<class H> class LList
{
    int n;
    Node<H> *header, *trailer, *current;

    Node<H>* _searchPre(H x)
    {
      Node<H> *pre = header;
			Node<H> *tmp = header->getNext();
			while(tmp != trailer) {
				if(*tmp->getKey() == x) return pre;
				pre = tmp;
				tmp = tmp->getNext();
			}
			return NULL;
    }

  public:
    LList()
    {
      trailer = new Node<H>();
      header = new Node<H>(NULL, trailer);
      n = 0;
    }

    LList<H>* ins(H x)
    {
      Node<H> *nd = new Node<H>(&x);
      Node<H> *tmp = header->getNext();
      Node<H> *pre = header;
    while(tmp != trailer && *tmp->getKey() < x)
    {
      pre = tmp;
      tmp = tmp->getNext();
    }
      pre->setNext(nd);
      nd->setNext(tmp);
      n++;
      return this;
    }

    LList<H>* del(H e)
    {
      Node<H> *tmp = _searchPre(e);
      if(!tmp)  return this;
      Node<H> *nd = tmp->getNext();
			tmp->setNext(nd->getNext());
			delete(nd);
	                 n--;
       return this;
    }

    bool search(H x)
    {
      return _searchPre(x) != NULL;
    }

    H* begin()
    {
      if(header->getNext() == trailer)
	return NULL;
      current = header->getNext();
      return current->getKey();
    }

    H* next()
    {
      if(current == trailer)
	return NULL;
      if(current->getNext() == trailer)
	return NULL;
      current = current->getNext();
      return current->getKey();
    }

    void print()
    {
      Node<H> *tmp = header->getNext();
      while(tmp != trailer)
      {
        cout << *tmp->getKey() << " ";
        tmp = tmp->getNext();
      }
      cout << endl;
    }

    void printIterator()
    {
      for(H* it = begin(); it; it = next())
        cout << *it << " ";
      cout << endl;
    }

};

// Overloading operator << LList
template<class H> ostream &operator<<(ostream &os, LList<H> &obj)
{
	for(H* it = obj.begin(); it; it = obj.next())
	  os << *it << " ";
	return os << endl;
}

/******************* Main *******************/
int main()
{
    LList<int> *l = new LList<int>();
    l->ins(7)->ins(2)->ins(-9);
    cout << l->search(7) << endl;
    l->print();
    l->printIterator();
    cout << *l;
    l->del(3)->del(7)->del(-9);
    cout << l->search(7) << endl;
    l->print();
    l->printIterator();
    cout << *l;


    cin.get();
    return 0;
}
