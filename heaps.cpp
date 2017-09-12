#include <iostream>

using namespace std;

class Heap
{
public:
    Heap(int sz) : a{new int[sz]}, n{sz} {}
    Heap(int arr[], int sz);
    ~Heap() { delete []a; }
    void maxHeapify(int i);
    void buildMaxHeap();
    void heapsort();
    friend ostream &print(ostream &os, const Heap &heap);
private:
    // helper functions
    int left(int i) { return 2*i + 1; }
    int right(int i) { return 2*i + 2; }
    int parent(int i) { return i/2 - 1; }

    int *a;
    int n;
    int heapSize = 0;
};

ostream &print(ostream &os, const Heap &heap)
{
    for (int i = 0; i < heap.n; ++i)
        os << heap.a[i] <<  " ";
    return os;
}

Heap::Heap(int arr[], int sz) : a{new int[sz]}, n{sz}
{
    for (int i = 0; i < sz; ++i)
        a[i] = arr[i];
    buildMaxHeap();
}

void Heap::maxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heapSize && a[l] > a[largest])
        largest = l;
    if (r < heapSize && a[r] > a[largest])
        largest = r;
    if (largest != i)
    {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        return maxHeapify(largest);
    }
}

void Heap::buildMaxHeap()
{
    heapSize = n;
    for (int i = n/2; i >= 0; --i)
        maxHeapify(i);
}

void Heap::heapsort()
{
    while (heapSize > 1)
    {
        int temp  = a[heapSize - 1];
        a[heapSize - 1] = a[0];
        a[0] = temp;
        --heapSize;
        maxHeapify(0);
    }
}

int main()
{
    const int n = 10;
    int a[n] = {0};

    cout << "Enter elements: ";
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    Heap h(a, n);
    print(cout, h) << endl;
    h.heapsort();
    cout << "Heapsort: ";
    print(cout, h) << endl;
    return 0;
}
