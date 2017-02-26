/* Coded by ©ZMDevJockey */

/*
ArrayStack Template
*/

#include <iostream>

using namespace std;


/******************* Class ArrayStack *******************/
template<class H> class ArrayStack
{
		H *s;
		int length, n;

	public:
		ArrayStack(int length = 100)
		{
			this->length = length;
			s = new H[length];
			n = 0;
		}

		ArrayStack<H>* push(H x)
		{
			if(isFull()) cout << "Stack is full!\n";
			else
			{
				s[n] = x;
				n++;
			}
			return this;
		}

		H* pop()
		{
			if(isEmpty()) cout << "Stack is empty\n";
			else
			{
				n--;
				return &s[n];
			}
			return NULL;
		}

		bool isFull() { return length == n; }

		bool isEmpty() { return n == 0; }

		void print()
		{
			for(int i = 0; i < n; i++)
				cout << s[i] << " ";
			cout << endl;
		}

		int getSize() { return n; }

};


/******************* Main *******************/
int main()
{
	ArrayStack<int> *s = new ArrayStack<int>();
    s->push(3)->push(6)->push(2);
    s->print();
    s->pop();
    s->print();


	cin.get();
	return 0;
}
