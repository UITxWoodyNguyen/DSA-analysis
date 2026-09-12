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
        int localSum = 0;
        for (int j = i; j < n; j++)
        {
            localSum += a[j];
            globalSum = max(localSum, globalSum);
        }
    }

    cout << globalSum;
}



// -2 11 -4 13 -5 -2 