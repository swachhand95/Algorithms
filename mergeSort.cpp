#include <iostream>
#include <fstream>

using namespace std;

/*
 * This program sorts using Merge Sort and also counts the number of inversions
 */

/*
 * Merges two subarrays and returns the number of split inversions
 * p = start of 1st/original array
 * q = mid of original array
 * r = end of 2nd/original array
 */
template <typename T>
long long int merge(T a[], size_t p, size_t q, size_t r)
{
    long long int inversions = 0;

    // Split and copy the original array into left and right arrays
    size_t n1 = q - p + 1;
    size_t n2 = r - q;

    T *L = new T[n1];
    T *R = new T[n2];

    for (size_t i = 0; i < n1; ++i)
        L[i] = a[p + i];
    for (size_t i = 0; i < n2; ++i)
        R[i] = a[q + 1 + i];

    // Merge the L and R arrays into array 'a'
    size_t i = 0, j = 0, k = p;

    while (k <= r && i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
        {
            // Increment the no. of inversions when you copy an element from the
            // R subarray while the L subarray is still not over.
            inversions += (n1 - i);
            a[k++] = R[j++];
        }
    }

    // Copy the leftover elements of L
    while (k <= r && i < n1)
        a[k++] = L[i++];

    // Copy the leftover elements of R
    while (k <= r && j < n2)
        a[k++] = R[j++];

    delete []L;
    delete []R;

    return inversions;
}

/*
 * Sorts array 'a' using Merge Sort and returns the total number of inversions
 */
template <typename T>
long long int mergeSort(T a[], size_t start, size_t end)
{
    if (end <= start)
        return 0;

    size_t mid = start + (end - start)/2;

    long long int invL = mergeSort(a, start, mid);          // Left inversions
    long long int invR = mergeSort(a, mid + 1, end);        // Right inversions
    long long int invSplit = merge(a, start, mid, end);     // Split inversions

    return invL + invSplit + invR;
}

/*
 * Utility function to display an array
 */
template <typename T, unsigned N>
void printArr(const T (&a)[N])
{
    for (size_t i = 0; i != N; ++i)
        cout << a[i] << " ";
    cout << endl;
}

/*
 * Subroutine to test mergeSort
 */
void mergeSortTest()
{
    int arr[] = {3, 2, 4, 5, 1, -1, 4};
    printArr(arr);

    long long int inv = mergeSort(arr, 0, 6);
    printArr(arr);

    cout << "Inversions = " << inv << endl;
}

int main()
{
//    mergeSortTest();

    ifstream fin("IntegerArray.txt");

    const long long int sz = 100000;
    long long int arr[sz] = {0};

    for (long long int i = 0; i != sz; ++i)
        fin >> arr[i];

    cout << "Inversions = " << mergeSort(arr, 0, sz - 1) << endl;
}
