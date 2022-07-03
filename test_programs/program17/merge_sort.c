// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
//#include <stdio.h>
/* UTILITY FUNCTIONS */
void mergeSort(int arr[], int l, int r) __attribute__((noinline));
void merge(int arr[], int l, int m, int r) __attribute__((noinline));
 
/* Driver code */
int _start()
{
    int arr[5];


    arr[0] = 12;
    arr[1] = 11;
    arr[2] = 7;
    arr[3] = 50;
    arr[4] = 26;
    // arr[2] = 13;
    // arr[3] = 5;
    // arr[4] = 6;
    // arr[5] = 7;

    int arr_size = 5;
 
    mergeSort(arr, 0, arr_size - 1);

    // for(int i=0;i<2;i++)
    // {
    //     printf("%d ",arr[i]);
    // }
 
    return 0;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1];
    int R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
 