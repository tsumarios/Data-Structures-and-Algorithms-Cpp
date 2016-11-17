/* Coded by Z Ov3rFlow */
 
/*
BubbleSort
*/
 
//Swap elements / Swap degli elementi
static void swap(int a[], int first, int second)
{
    int tmp;
    tmp = a[first];
    a[first] = a[second];
    a[second] = tmp;
}
 
 
//BubbleSort
static void bubbleSort(int a[], int N)
{
    for(int i = 1; i < N; i++)
        for(int j = 0; j < N-i; j++)
            if(a[j] > a[j+1])
                swap(a, j, j+1);
}
