#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

void print(int *A, int n) {
	for(int i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;
}

void CountingSort(int *A, int n) {
	// A:array; n: dimensione; k: valore massimo
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++) {
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	int range = max-min+1;
	int *B = new int[n];
	int *C = new int[range];
	for(int i=0; i<=range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i]-min]++;
	for(int i=1; i<=range; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[A[i]-min]-1] = A[i];
		C[A[i]-min]--;
	}
	for(int i=0; i<n; i++) A[i] = B[i];
}

void CountingSort2(int *A, int n) {
	// A:array; n: dimensione; k: valore massimo
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++) {
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	int range = max-min+1;
	int *C = new int[range];
	for(int i=0; i<=range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i]-min]++;
	int j = 0;
	int k = 0;
	while(j<n) {
		while(C[k]>0) {
			A[j++]=k+min;
			C[k]--;
		}
		k++;	
	}
}


int main() {
	int A[] = {374, 372, 370, 372, 371, 375, 371, 371, 373, 374};
	int n = 10;
	print(A,n);
	CountingSort2(A,n);
	print(A,n);
	int B[] = {};
	A = B;
	
}
