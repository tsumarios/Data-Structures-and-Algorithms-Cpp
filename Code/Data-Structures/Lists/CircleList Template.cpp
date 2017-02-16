/* Coded by ©ZMDevJockey */

/*
CircleList Template
*/

#include <iostream>

using namespace std;


/******************* Class Node *******************/
template<class H> class Node
{
    Node<H> *prev, *next;
    H *key;

  public:
    Node(H *key, Node<H> *prev = NULL, Node<H> *next = NULL)
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
    bool hasNext() { return next ? 1:0;}
};


/******************* Class CList *******************/
template<class H> class CList
{
  int n;
  Node<H> *cursor;

  Node<H>* _maxNode()
  {
    if(!cursor) return NULL;
    Node<H> *tmp = cursor;
    Node<H> *max = cursor;
    for(int i = 0; i < n; i++)
    {
      if(*tmp->getKey() > *max->getKey()) max = tmp;
      tmp = tmp->getNext();
    }
    return max;
  }

  Node<H>* _searchNode(H x)
  {
    if(!cursor) return NULL;
    Node<H> *tmp = cursor;
    for(int i = 0; i < n; i++)
    {
      if(*tmp->getKey() == x) return tmp;
      tmp = tmp->getNext();
    }
    return NULL;
  }

public:
  CList() : n(0), cursor(NULL) {}

  int getSize() { return n; }

  void ins(H x) {
    Node<H> *nd = new Node<H>(&x);
    n++;
    if(!cursor)
    {
      cursor = nd;
      nd->setPrev(nd);
      nd->setNext(nd);
    }
    else
    {
      nd->setPrev(cursor);
      nd->setNext(cursor->getNext());
      nd->getNext()->setPrev(nd);
      cursor->setNext(nd);
      cursor = _maxNode();
    }
  }

  void del(H x) {
    Node<H> *tmp = _searchNode(x);
    if(!tmp) return;
    if(n == 1) cursor = NULL;
    else
    {
      if(cursor == tmp) cursor = tmp->getNext();
      tmp->getPrev()->setNext(tmp->getNext());
      tmp->getNext()->setPrev(tmp->getPrev());
      cursor = _maxNode();
    }
    delete tmp;
    n--;
  }

  void print()
  {
    if(!cursor) return;
    Node<H> *tmp = cursor;
    for(int i = 0; i < n; i++)
    {
        cout << *tmp->getKey() << " ";
        tmp = tmp->getNext();
      }
    cout << endl;
  }

};


/******************* Main *******************/
int main()
{
    CList<int> *c = new CList<int>();
    c->ins(3);
    c->ins(6);
    c->print();

    c->del(6);
    c->print();


    cin.get();
    return 0;
}
