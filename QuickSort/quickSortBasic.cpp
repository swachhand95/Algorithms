#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int choosePivot(int l, int r)
{
    int sz = r - l + 1;
    int p = rand() % sz + l;
    return p;
}

void partitionArray(int arr[], int l, int p, int r)
{
    swap(arr[l], arr[p]);
    int i = l;
    int j = l + 1;
    while (j <= r)
    {
        if (arr[j] < arr[l])
        {
            swap(arr[j], arr[i+1]);
            ++i;
        }
        ++j;
    }
    swap(arr[l], arr[i]);
}

void quickSort(int arr[], int l, int r)
{
    if (r <= l) return;
    int p = choosePivot(l, r);
    partitionArray(arr, l, p, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
}

int main()
{
    int arr[] = {3,8,2,5,1,4,7,6};
    quickSort(arr, 0, 7);
    for (int i = 0; i < 8; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}

