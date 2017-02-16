/* Coded by ©ZMDevJockey */
 
/*
Double Linked List Template
*/
 
#include <iostream>
 
using namespace std;
 
/******************* Class Node *******************/
template<class H> class Node
{
    H *key;
    Node<H> *prev, *next;
 
  public:
    Node(H *key = NULL,Node<H> *prev = NULL,Node<H> *next = NULL)
    {
      if(key) this->key = new H(*key);
      else    this->key = NULL;
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
 
 
/******************* Class DBList  *******************/
template<class H> class DBList
{
    int n;
    Node<H> *header, *trailer, *current;
 
    void insAfter(Node<H> *tmp, H x)
    {
      Node<H> *nd = new Node<H>(&x,tmp,tmp->getNext());
      tmp->setNext(nd);
      nd->getNext()->setPrev(nd);
      n++;
    }
 
    Node<H>* _search(H x)
    {
      Node<H> *tmp = header->getNext();
      while(tmp != trailer)
      {
        if(x == *tmp->getKey())
          return tmp;
        tmp = tmp->getNext();
      }
      return NULL;
    }
 
  public:
    DBList()
    {
      n = 0;
      trailer = new Node<H>(NULL);
      header = new Node<H>(NULL,NULL,trailer);
      trailer->setPrev(header);
    }
 
    DBList<H>* insHead(H x)
    {
      insAfter(header, x);
      return this;
    }
 
    DBList<H>* insTail(H x)
    {
      insAfter(trailer->getPrev(), x);
      return this;
    }
 
    DBList<H>* del(H x)
    {
      Node<H> *tmp = _search(x);
      if(!tmp)
        return this;
      tmp->getPrev()->setNext(tmp->getNext());
      tmp->getNext()->setPrev(tmp->getPrev());
      delete tmp;
      n--;
      return this;
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
 
    bool search(H x)
    {
      return _search(x)!=NULL;
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
 
//Overloading operator << for DBList class
template<class H> ostream &operator<<(ostream &os, DBList<H> &obj)
{
  for(H* it = obj.begin(); it; it = obj.next())
    os << *it << " ";
  return os << endl;
}
 
/******************* Main *******************/
int main()
{
    DBList<int> *l = new DBList<int>();
    l->insHead(5)->insHead(4)->insTail(1);
    l->print();
    l->printIterator();
    cout << *l;
    l->del(4);
    l->print();
    l->printIterator();
    cout << *l;
 
 
    cin.get();
    return 0;
}
