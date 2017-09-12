#include <iostream>

using namespace std;

void insertionSort(int arr[], int size) 
{
	for (int j = 1; j < size; ++j) 
	{
		int key = arr[j];
		
		int i = j - 1;
		while (i >= 0 && arr[i] > key)
		{
			arr[i + 1] = arr[i];
			--i;
		}

		arr[i + 1] = key;
	}
}

int binarySearchIterative(int arr[], int size, int val) 
{
	int start = 0;
	int finish = size - 1;
	while (start <= finish) 
	{
		int mid = (finish - start)/2 + start;
		if (val == arr[mid]) 
			return  mid;
		else if (val < arr[mid])
			finish = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}

int binarySearchRecursive(int arr[], int start, int finish, int val)
{
	if (start > finish)
		return -1;
	int mid = (finish - start)/2 + start;
	if (val == arr[mid])
		return mid;
	else if (val > arr[mid])
		return binarySearchRecursive(arr, mid + 1, finish, val);
	else if (val < arr[mid])
		return binarySearchRecursive(arr, start, mid - 1, val);
}

int main()
{
	int arr[] = {5, 2, 4, 6, 1, 3};

	insertionSort(arr, 6);

	for (int i = 0; i < 6; ++i)
		cout << arr[i] << " ";
	cout << endl;

	cout << binarySearchRecursive(arr, 0, 5, 1) << endl;
	cout << binarySearchRecursive(arr, 0, 5, 6) << endl;
	cout << binarySearchRecursive(arr, 0, 5, 4) << endl;
	cout << binarySearchRecursive(arr, 0, 5, 7) << endl;

	for (int i = 0; i < 6; ++i)
		cout << arr[i] << " ";
	cout << endl;
}