#include <vector>
#include <algorithm>
#include <climits>
#include<iostream>
using namespace std;
int maxCrossingSum(int a[], int left,int mid,int right){
    int sum =0;
    int left_sum = INT_MIN;
    for (int i = mid; i >= left; --i) {
        sum += a[i];
        if (sum > left_sum) left_sum = sum;
        sum = 0;
    int right_sum = INT_MIN;
    for (int i = mid + 1; i <= right; ++i) {
        sum += a[i];
        if (sum > right_sum) right_sum = sum;
    }
    return left_sum + right_sum;
    }
}
int maxSubArrayHelp(int a[],int left,int right){
    if (left == right) {
        return a[left];
    }

    int mid = left + (right - left) / 2;
    int max_left = maxSubArrayHelp(a,left,mid);
    int max_right = maxSubArrayHelp(a,mid+1,right);
    int max_cross = maxCrossingSum(a, left, mid, right);
    return max({max_left, max_right, max_cross});
}
int maxSubArray(int a[]){
    return maxSubArrayHelp(a,0,a.size()-1);
}

int main(){
    int n;
    cin >> n;
    int a[n];
    for (int i=0;i < n;i++){
        cin >> a[i];
    }
    int h = maxSubArray(a);
    cout <<h<<endl;
}