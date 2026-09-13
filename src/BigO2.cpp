#include <iostream>
using namespace std;

int maxO2(int a[], int size)
{
    int max = a[0];
    for (int i = 0; i < size; i++)
    {
        int temp = 0;
        for (int j = i; j < size; j++)
        {
            temp += a[j];
            if (max < temp)
            {
                max = temp;
            }
        }
    }
    return max;
}

int main()
{
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int h = maxO2(a, n);
    cout << h << endl;
}