#include <bits/stdc++.h>
#include <ctime>

using namespace std;

int main()
{
    int n; cin >> n;
    int a[n];
    int globalSum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int localSum = 0;
            for (int k = i; k <= j; k++)
            {
                localSum += a[k];
            }

            if (globalSum < localSum) globalSum = localSum; 
        }
    }

    cout << globalSum;

}



// -2 11 -4 13 -5 -2 