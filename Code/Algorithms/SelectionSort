/* Z Ov3rFlow */

/*
SelectionSort
*/

//Swap elements / Swap degli elementi
static void swap(int a[], int first, int second)
{
	int tmp;
	tmp = a[first];
	a[first] = a[second];
	a[second] = tmp;
}

//SelectionSort
void selectionSort(int a[], int N)
{
	int min;
	for(int i = 0; i < N-1; i++)
	{
		min = i;
		for(int j = i+1; j < N; j++)
			if(a[j] < a[min])
				min = j;
		swap(a, min, i);
	}
}
