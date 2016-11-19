/* Coded by Z Ov3rFlow */

/*
ArrayQueue Template
*/

#include <iostream>

using namespace std;

/******************* Class ArrayQueue *******************/
template<class H> class ArrayQueue
{
    H *q;
    int n, length, head, tail;

  public:
    ArrayQueue(int length = 5)
    {
      n = head = tail = 0;
      this->length = length;
      q = new H[length];
    }

    bool isFull() { return n==length; }
    bool isEmpty() { return n==0; }
    int getSize() { return n; }

    ArrayQueue<H>* enqueue(H x)
    {
      if(!isFull())
      {
        q[tail] = x;
        tail = (tail+1) % length;
        n++;
      }
      return this;
    }

    H* dequeue()
    {
      if(isEmpty()) return NULL;
      int tmp = head;
      head = (head+1) % length;
      n--;
      return &q[tmp];
    }

    void print()
    {
      if(!isEmpty())
      {
        cout << q[head] << " ";
        for(int i = head+1; i != tail; i++)
          cout << q[i] << " ";
      }
      cout << endl;
    }

};


/******************* Main *******************/
int main()
{
    ArrayQueue<int> *q = new ArrayQueue<int>();
    q->enqueue(4)->enqueue(9)->enqueue(2);
    q->print();

    q->dequeue();
    q->print();


    cin.get();
    return 0;
}
