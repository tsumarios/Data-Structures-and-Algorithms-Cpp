/* Coded by ©ZMDevJockey */
 
/*
InsertionSort
*/

void insertionSort(int a[], int N)
{
	for(int i = 1; i < N; i++)
	{
		int key = a[i];
		int position = i;

		//it shifts values larger than key to right / shifta i valori più grandi di key a destra
		while(position > 0 && a[position-1] > key)
		{
			a[position] = a[position-1];
			position--;
		}

		a[position] = key;
	}
}
