#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int globalSum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int localSum = 0;
            for (int k = i; k <= j; k++)
            {
                localSum += a[k];
            }

            if (globalSum < localSum)
                globalSum = localSum;
        }
    }

    cout << globalSum;
    delete[] a;
}