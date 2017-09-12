#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <cstdlib>
#include <iostream>

int choosePivotRandom(int min, int max);
int choosePivotRandom2(int min, int max);
int choosePivotMin(int min, int max);
int choosePivotMax(int min, int max);

template <typename T>
int choosePivotMedian(T a[], int start, int mid, int end)
{
    int minIdx = start;
    if (a[start] < a[mid])
    {
        if (a[start] < a[end])
            minIdx = start;
        else
            minIdx = end;
    }
    else
    {
        if (a[mid] < a[end])
            minIdx = mid;
        else
            minIdx = end;
    }

    int maxIdx = end;
    if (a[start] > a[mid])
    {
        if (a[start] > a[end])
            maxIdx = start;
        else
            maxIdx = end;
    }
    else
    {
        if (a[mid] > a[end])
            maxIdx = mid;
        else
            maxIdx = end;
    }

    if (start != minIdx && start != maxIdx)
        return start;
    if (mid != minIdx && mid != maxIdx)
        return mid;
    if (end != minIdx && end != maxIdx)
        return end;
}

// Partitions an array around a pivot
template <typename T>
int partitionArray(T a[], int l, int p, int r)
{
    T pivot = a[p];
    std::swap(a[l], a[p]);

    int i = l + 1;
    for (int j = l + 1; j <= r; ++j)
    {
        if (pivot > a[j])
        {
            std::swap(a[i], a[j]);
            ++i;
        }
    }
    std::swap(a[i-1], a[l]);
    return i - 1;
}

// Sorts an array using Quick Sort and returns the number of comparisons made
template <typename T>
long long int quickSort(T a[], int l, int r)
{
    if (r <= l)
        return 0;

    int sz = r - l + 1;
    int mid = 0;
    if (sz % 2 == 0)
        mid = l + sz/2 - 1;
    else
        mid = l + sz/2;

    int p = choosePivotMedian(a, l, mid, r);
    p = partitionArray(a, l, p, r);

    long long int cmpL = quickSort(a, l, p - 1);
    long long int cmpR = quickSort(a, p + 1, r);

    return cmpL + cmpR + (r - l);
}

#endif // QUICKSORT_H_INCLUDED

// 162085
// 164123
// 159894
