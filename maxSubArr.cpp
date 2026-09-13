#include <iostream>
#include <climits>
#include <chrono>
#include <thread>
#include <future>
using namespace std;
using namespace std::chrono;

class MaxSubArray {
private:
    int n;
    int* a;

    int maxCrossingSum(int left, int mid, int right) {
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

    int maxSubArrayHelp(int left, int right) {
        if (left == right) return a[left];
        int mid = left + (right - left) / 2;
        int max_left = maxSubArrayHelp(left, mid);
        int max_right = maxSubArrayHelp(mid + 1, right);
        int max_cross = maxCrossingSum(left, mid, right);
        int max_val = max_left;
        if (max_right > max_val) max_val = max_right;
        if (max_cross > max_val) max_val = max_cross;
        return max_val;
    }

public:
    MaxSubArray(int n_, int* arr) : n(n_), a(arr) {}

    void BigOn() {
        auto start = high_resolution_clock::now();
        int maxSum = a[0], currentSum = a[0];
        for (int i = 1; i < n; i++) {
            if (currentSum + a[i] > a[i]) currentSum = currentSum + a[i];
            else currentSum = a[i];
            if (currentSum > maxSum) maxSum = currentSum;
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << maxSum << "\nRuntime: " << duration << " ms\n";
    }

    void BigOnlogn() {
        auto start = high_resolution_clock::now();
        int result = maxSubArrayHelp(0, n - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << result << "\nRuntime: " << duration << " ms\n";
    }

    void BigOn2() {
        auto start = high_resolution_clock::now();
        int max = a[0];
        for (int i = 0; i < n; i++) {
            int temp = 0;
            for (int j = i; j < n; j++) {
                temp += a[j];
                if (max < temp) max = temp;
            }
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << max << "\nRuntime: " << duration << " ms\n";
    }

    void BigOn3() {
        auto start = high_resolution_clock::now();
        int globalSum = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int localSum = 0;
                for (int k = i; k <= j; k++) localSum += a[k];
                if (globalSum < localSum) globalSum = localSum;
            }
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << globalSum << "\nRuntime: " << duration << " ms\n";
    }
};

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    MaxSubArray msa(n, a);

    cout << "=== O(n) ===\n";
    msa.BigOn();

    cout << "\n=== O(n log n) ===\n";
    msa.BigOnlogn();

    cout << "\n=== O(n^2) ===\n";
    msa.BigOn2();

    cout << "\n=== O(n^3) ===\n";
    msa.BigOn3();

    delete[] a;
    return 0;
}