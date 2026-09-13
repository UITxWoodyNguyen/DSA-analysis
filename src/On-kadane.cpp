#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int maxSum = a[0], currentSum = a[0];
    for (int i = 1; i < n; i++)
    {
        if (currentSum + a[i] > a[i])
            currentSum = currentSum + a[i];
        else
            currentSum = a[i];
        
        if (currentSum > maxSum)
            maxSum = currentSum;
    }
    cout << maxSum;
    delete[] a;
}