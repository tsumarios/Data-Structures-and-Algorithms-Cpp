/* Coded by ©ZMDevJockey */

/*
List of Trees Template
*/

#include <iostream>

using namespace std;


/******************* Class TNode *******************/
template<class H> class TNode
{
    H *key;
    TNode<H> *left, *right, *parent;

  public:
    TNode(H *key = NULL, TNode<H> *left = NULL, TNode<H> *right = NULL, TNode<H> *parent = NULL)
    {
      if(key) this->key = new H(*key);
      else    this->key = NULL;
      this->left = left;
      this->right = right;
      this->parent = parent;
    }

    void setLeft(TNode<H> *left) { this->left = left; }
    void setRight(TNode<H> *right) { this->right = right; }
    void setParent(TNode<H> *parent) { this->parent = parent; }
    void setKey(H *key) { this->key = new H(*key); }

    TNode<H>* getLeft() { return left; }
    TNode<H>* getRight() { return right; }
    TNode<H>* getParent() { return parent; }
    H* getKey() { return new H(*key); }

};


/******************* Class BSTree *******************/
template<class H> class BSTree
{
    TNode<H> *root, *current;
    int n;

    TNode<H>* _minimum(TNode<H> *x)
    {
      if(!x)  return NULL;
      while(x->getLeft()) x = x->getLeft();
      return x;
    }

    TNode<H>* _succ(TNode<H> *x)
    {
      if(!x)  return NULL;
      if(x->getRight()) return _minimum(x->getRight());

      TNode<H> *y = x->getParent();
      while(y && y->getRight() == x)
      {
        x = y;
        y = y->getParent();
      }
      return y;
    }

    TNode<H>* _searchNode(H e)
    {
      if(!root)  return NULL;
      TNode<H> *x = root;
      while(x && e != *x->getKey())
      {
        if(e < *x->getKey())  x = x->getLeft();
        else                  x = x->getRight();
      }
      return x;
    }

    BSTree<H>* _del(TNode<H> *tmp)
    {
      if(!root) return this;
      /* First Case */
      if(!tmp->getLeft() && !tmp->getRight())
      {
        TNode<H> *y = tmp->getParent();
        if(!y)  root = NULL;
        else
          if(y->getLeft() == tmp) y->setLeft(NULL);
          else                    y->setRight(NULL);
        delete tmp;
        n--;
        return this;
      }
      /* Second Case */
      if(tmp->getLeft() && tmp->getRight())
      {
        TNode<H> *s = _succ(tmp);
        tmp->setKey(s->getKey());
        _del(s);
        return this;
      }
      /* Third Case */
      TNode<H> *y = tmp->getParent();
      TNode<H> *z = tmp->getLeft();
      if(!z)  z = tmp->getRight();
      if(!y)  root = z;
      else
        if(y->getLeft() == tmp) y->setLeft(z);
        else                    y->setRight(z);
      z->setParent(y);
      delete tmp;
      n--;
      return this;
    }

  public:
    BSTree(): root(NULL), n(0) { begin(); }

    BSTree<H>* ins(H x)
    {
      TNode<H> *nd = new TNode<H>(&x);
      if(!root)
      {
        root = nd;
        n++;
        return this;
      }
      TNode<H> *tmp = root;
      TNode<H> *par = NULL;
      while(tmp)
      {
        par = tmp;
        if(x < *tmp->getKey()) tmp = tmp->getLeft();
        else                   tmp = tmp->getRight();
      }
      if(x < *par->getKey())  par->setLeft(nd);
      else                    par->setRight(nd);
      nd->setParent(par);
      n++;
      return this;
    }

    BSTree<H>* del(H x)
    {
      TNode<H> *tmp = _searchNode(x);
      if(tmp) _del(tmp);
      return this;
    }

    H* begin()
    {
      current = _minimum(root);
      if(current)  return current->getKey();
      return NULL;
    }

    H* next()
    {
      if(current)  current = _succ(current);
      if(current) return current->getKey();
      return NULL;
    }

    bool search(H x)
    {
      return _searchNode(x)!=NULL;
    }

    int getSize() { return n; }

    void print()
    {
      for(H *it = begin(); it; it = next())
        cout << *it << " ";
      cout << endl;
    }

};

//Overloading operator << BSTree
template<class H> ostream &operator<<(ostream &os, BSTree<H> &obj)
{
  for(H *it = obj.begin(); it; it = obj.next())
    os << *it << " ";
  return os << endl;
}


/******************* Class LNode *******************/
template<class H> class LNode
{
    LNode<H> *prev, *next;
    H *key;

  public:
    LNode(H *key = NULL, LNode<H> *prev = NULL, LNode<H> *next = NULL)
    {
      if(key) this->key = new H(*key);
      else    this->key = NULL;
      this->prev = prev;
      this->next = next;
    }

    LNode<H>* getPrev() { return prev; }
    LNode<H>* getNext() { return next; }
    H* getKey() { return new H(*key); }

    void setPrev(LNode<H> *prev) { this->prev = prev; }
    void setNext(LNode<H> *next) { this->next = next; }
    void setKey(H *key) { this->key = new H(*key); }

};


/******************* Class DBList *******************/
template<class H> class DBList
{
    LNode<H> *header, *trailer, *current;
    int n;

    LNode<H>* _search(H x)
    {
      LNode<H> *tmp = header->getNext();
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
      trailer = new LNode<H>(NULL);
      header = new LNode<H>(NULL, NULL, trailer);
      trailer->setPrev(header);
    }

    void insHead(H *x) {
			LNode<H> *nd = new LNode<H>(x);
			nd->setPrev(header);
			nd->setNext(header->getNext());
			header->setNext(nd);
			nd->getNext()->setPrev(nd);
		}

    void del(H *x) {
			LNode<H> *tmp = _search(x);
			if(!tmp) return;
			tmp->getNext()->setPrev(tmp->getPrev());
			tmp->getPrev()->setNext(tmp->getNext());
		}

    H* begin()
    {
      if(header->getNext() == trailer)  return NULL;
      current = header->getNext();
      return current->getKey();
    }

    H* next()
    {
      if(current == trailer)  return NULL;
      if(current->getNext() == trailer) return NULL;
      current = current->getNext();
      return current->getKey();
    }

    bool search(H x)
    {
      return _search(x)!=NULL;
    }

    void print()
    {
      for(H *it = begin(); it; it = next())
        cout << *it << " ";
      cout << endl;
    }

};

//Overloading operator << DBList
template<class H> ostream &operator<<(ostream &os, DBList<H> &obj)
{
    for(H *it = obj.begin(); it; it = obj.next())
      os << *it << " ";
    return os << endl;
}


/******************* Class LOT *******************/
template<class H> class LOT
{
    DBList< BSTree<H> > *l;
    int k;

  public:
    LOT(int k)
    {
      l = new DBList< BSTree<H> >();
      this->k = k;
    }

    LOT<H>* insert(H x)
    {
      BSTree<H> *t = l->begin();

      if(!t || t->getSize() >= k)
      {
        BSTree<H> *nt = new BSTree<H>();
        nt->ins(x);
        l->insHead(nt);
      }
      else
        t->ins(x);
      return this;
    }

    LOT<H>* del(H x)
    {
      for(BSTree<H> *i = l->begin(); i; i = l->next())
        i->del(x);
      return this;
    }

    void print()
    {
      cout << *l << endl;
    }

};


/******************* Main *******************/
int main()
{
    LOT<int> *l = new LOT<int>(4);
    l->insert(2)->insert(3)->insert(1)->insert(5)->insert(3)->insert(7)->insert(6);
    l->insert(1)->insert(2)->insert(4)->insert(5)->insert(3)->insert(2)->insert(1);
    l->del(5)->del(1)->del(2);
    l->print();

    cin.get();
    return 0;
}
