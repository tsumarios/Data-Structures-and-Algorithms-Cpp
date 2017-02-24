/* Coded by ©ZMDevJockey */

/*
Counting Sort							
*/

#include <iostream>

using namespace std;


/**************************
Counting Sort
**************************/
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
	for(int i = 0; i < n; i++)	C[A[i]-min]++;

	int j = 0, k = 0;
	while(j < n)
	{
		while(C[k] > 0)
		{
			A[j++] = k+min;
			C[k]--;
		}
		k++;
	}
}

/* Method printing an int array */
void print(int *A, int n)
{
	for(int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}


/*********************************** Main ***********************************/
int main()
{
	int n = 7;
	int A[] = {3,4,7,1,2,9,5};
	print(A,n);

	countingSort(A,n);
	print(A,n);

	cin.get();
	return 0;
}
