#include "QuickSort.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// Utility function to display an array
template <typename T, unsigned N>
void printArr(const T (&a)[N])
{
    for (size_t i = 0; i != N; ++i)
        cout << a[i] << " ";
    cout << endl;
}

void quickSortTest()
{
    int arr[] = {3, 2, 5, 1, 7, 6, 8, 0};
    printArr(arr);

    quickSort(arr, 0, 7);
    printArr(arr);
}

void medianTest()
{
    int arr[] = {4, 5, 6, 7};

    int start = 0, end = 3;
    int sz = end - start + 1;
    int mid = 0;
    if (sz % 2 == 0)
        mid = sz/2 - 1;
    else
        mid = sz/2;
    cout << arr[choosePivotMedian(arr, start, mid, end)] << endl;
}

int main()
{
    ifstream fin("QuickSort.txt");
    const int sz = 10000;

    int arr[sz] = {0};
    for (int i = 0; i != sz; ++i)
        fin >> arr[i];

    long long comparisons = quickSort(arr, 0, sz - 1);
    cout << "Number of comparisons made: " << comparisons << endl;
    printArr(arr);

    return 0;
}
