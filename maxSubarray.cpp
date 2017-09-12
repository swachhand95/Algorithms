#include <iostream>
#include <limits>

using namespace std;

#define MIN numeric_limits<int>::min()

int findMaxSubarray(int a[], int sz, int& left, int& right)
{
    left = right = 0;
    int sum = 0;
    int maxSum = MIN;

    for (int i = 0; i < sz; ++i)
    {
        for (int j = i; j < sz; ++j)
        {
            sum += a[j];
            if (sum > maxSum)
            {
                maxSum = sum;
                left = i;
                right = j;
            }
        }
        sum = 0;
    }

    return maxSum;
}

struct Subarray
{
    int l;
    int r;
    int sum;

    Subarray(int left = 0, int right = 0, int s = 0) :
        l(left), r(right), sum(s) {}
};

Subarray findMaxCrossingSubarray(int a[], int left, int mid, int right)
{
    int leftSum = MIN;
    int sum = 0;
    int leftIdx = 0;
    for (int i = mid; i >= left; --i)
    {
        sum += a[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            leftIdx = i;
        }
    }

    int rightSum = MIN;
    sum = 0;
    int rightIdx = 0;
    for (int i = mid + 1; i <= right; ++i)
    {
        sum += a[i];
        if (sum > rightSum)
        {
            rightSum = sum;
            rightIdx = i;
        }
    }

    return Subarray(leftIdx, rightIdx, leftSum + rightSum);
}

Subarray findMaxSubarray(int a[], int left, int right)
{
    if (left == right)
        return Subarray(left, left, a[left]);
    int mid = (right - left) / 2 + left;

    Subarray l = findMaxSubarray(a, left, mid);
    Subarray r = findMaxSubarray(a, mid + 1, right);
    Subarray cross = findMaxCrossingSubarray(a, left, mid, right);

    if (l.sum >= r.sum && l.sum >= cross.sum)
        return l;
    if (r.sum >= l.sum && r.sum >= cross.sum)
        return r;
    return cross;
}

int main()
{
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, 7};
    int sz = sizeof(a)/sizeof(a[0]);

    int left = 0, right = 0;

    int maxSum = findMaxSubarray(a, sz, left, right);

    cout << "Left = " << left
         << ", right = " << right
         << ", sum = " << maxSum << endl;

    Subarray maxSubarray = findMaxSubarray(a, 0, sz - 1);

    cout << "Left = " << maxSubarray.l
         << ", right = " << maxSubarray.r
         << ", sum = " << maxSubarray.sum << endl;

    return 0;
}
