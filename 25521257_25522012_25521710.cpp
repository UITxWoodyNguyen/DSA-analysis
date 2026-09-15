#include <iostream>
#include <climits>
using namespace std;

int maxOn(int a[], int n) {
    int maxSum = a[0], currentSum = a[0];
    for (int i = 1; i < n; i++) {
        if (currentSum + a[i] > a[i]) currentSum = currentSum + a[i];
        else currentSum = a[i];
        if (currentSum > maxSum) maxSum = currentSum;
    }
    return maxSum;
}

int maxCrossingSum(int a[], int left, int mid, int right) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = mid; i >= left; --i) {
        sum += a[i];
        if (sum > left_sum) left_sum = sum;
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= right; ++i) {
        sum += a[i];
        if (sum > right_sum) right_sum = sum;
    }
    return left_sum + right_sum;
}

int maxSubArrayHelp(int a[], int left, int right) {
    if (left == right) return a[left];
    int mid = left + (right - left) / 2;
    int max_left = maxSubArrayHelp(a, left, mid);
    int max_right = maxSubArrayHelp(a, mid + 1, right);
    int max_cross = maxCrossingSum(a, left, mid, right);
    int max_val = max_left;
    if (max_right > max_val) max_val = max_right;
    if (max_cross > max_val) max_val = max_cross;
    return max_val;
}

int maxOnlogn(int a[], int n) {
    return maxSubArrayHelp(a, 0, n - 1);
}

int maxOn2(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        int temp = 0;
        for (int j = i; j < n; j++) {
            temp += a[j];
            if (max < temp) max = temp;
        }
    }
    return max;
}

int maxOn3(int a[], int n) {
    int globalSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int localSum = 0;
            for (int k = i; k <= j; k++) localSum += a[k];
            if (globalSum < localSum) globalSum = localSum;
        }
    }
    return globalSum;
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << maxOn(a, n) << endl;
    cout << maxOnlogn(a, n) << endl;
    cout << maxOn2(a, n) << endl;
    cout << maxOn3(a, n) << endl;

    delete[] a;
    return 0;
}