/* Coded by ©ZMDevJockey */

/*
Binary Search Tree Template
*/

#include <iostream>

using namespace std;

/******************* Class Node *******************/
template<class H> class Node
{
    Node<H> *left, *right, *parent;
    H *key;

  public:
    Node(H *key = NULL, Node<H> *left = NULL, Node<H> *right = NULL, Node<H> *parent = NULL)
    {
      if(key)   this->key = new H(*key);
      else      this->key = NULL;
      this->left = left;
      this->right = right;
      this->parent = parent;
    }

    void setLeft(Node<H> *left) { this->left = left; }
    void setRight(Node<H> *right) { this->right = right; }
    void setParent(Node<H> *parent) { this->parent = parent; }
    void setKey(H *key) { this->key = new H(*key); }

    Node<H>* getLeft()  { return left; }
    Node<H>* getRight()  { return right; }
    Node<H>* getParent()  { return parent; }
    H* getKey()  { return new H(*key); }

};


/******************* Class BSTree *******************/
template<class H> class BSTree
{
    Node<H> *root, *current;
    int n;

    H* _search(Node<H>* x, H e)
    {
			if(!x) return 0;
			if(e == *x->getKey()) return x->getKey();
			if(e < *x->getKey()) return _search(x->getLeft(), e);
			else                 return _search(x->getRight(), e);
		}

    Node<H>* _searchNode(H e) {
			if(!root) return NULL;
			Node<H> *x = root;
			while(x && *x->getKey()!= e)
      {
				if(e < *x->getKey()) x = x->getLeft();
				else                 x = x->getRight();
			}
			return x;
		}

    Node<H>* _minimum(Node<H> *tmp)
    {
      if(!tmp)  return NULL;
      Node<H> *x = tmp;
      while(x->getLeft()) x = x->getLeft();
      return x;
    }

    Node<H>* _succ(Node<H> *tmp)
    {
      if(!tmp)  return NULL;
      if(tmp->getRight()) return _minimum(tmp->getRight());
      Node<H> *x = tmp;
      Node<H> *y = tmp->getParent();
      while(y && y->getRight() == x)
      {
        x = y;
        y = y->getParent();
      }
      return y;
    }

    BSTree<H>* _del(Node<H> *tmp)
    {
      if(!tmp) return this;
			/* primo caso */
			if(!tmp->getLeft() && !tmp->getRight())
      {
				Node<H> *y = tmp->getParent();
				if(!y) root = NULL;
				else
            if(y->getLeft() == tmp)  y->setLeft(NULL);
					  else                     y->setRight(NULL);
        delete tmp;
        n--;
				return this;
			}
			/* terzo caso */
			if(tmp->getLeft() && tmp->getRight())
      {
				Node<H>* s = _succ(tmp);
				tmp->setKey(s->getKey());
				_del(s);
				return this;
			}
			/* secondo caso */
			Node<H> *y = tmp->getParent();
			Node<H> *z = tmp->getLeft();
			if(!z) z = tmp->getRight();
			if(!y) root = z;
			else
				if(y->getLeft() == tmp) y->setLeft(z);
				else                    y->setRight(z);
			z->setParent(y);
      delete tmp;
      n--;
			return this;
    }

  public:
    BSTree(): root(NULL), n(0) {}

    BSTree<H>* ins(H x)
    {
      Node<H> *nd = new Node<H>(&x);
      if(!root)
      {
        root = nd;
        n++;
        return this;
      }
      Node<H> *tmp = root;
      Node<H> *par = NULL;
      while(tmp)
      {
        par = tmp;
        if(x < *tmp->getKey())  tmp = tmp->getLeft();
        else                    tmp = tmp->getRight();
      }
      if(x < *par->getKey())  par->setLeft(nd);
      else                    par->setRight(nd);
      nd->setParent(par);
      n++;
      return this;
    }

    BSTree<H>* del(H x)
    {
      Node<H>* tmp = _searchNode(x);
			if(tmp) _del(tmp);
			return this;
		}

		bool search(H e)
    {
			return _search(root,e) != NULL;
		}

    H* begin()
    {
      current = _minimum(root);
      if(!current)  return NULL;
      return current->getKey();
    }

    H* next()
    {
      if(current) current = _succ(current);
      if(current) return current->getKey();
      return NULL;
    }

    void print()
    {
        H *tmp = begin();
        while(tmp)
        {
          cout << *tmp << " ";
          tmp = next();
        }
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

/******************* Main *******************/
int main()
{
    BSTree<int> *t = new BSTree<int>();
    t->ins(4)->ins(1)->ins(6);
    t->print();
    cout << *t;
    cout << t->search(4) << endl;

    t->del(4);
    t->print();
    cout << *t;
    cout << t->search(4) << endl;

    cin.get();
    return 0;
}
