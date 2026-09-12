#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
int maxO2(int a[], int size){
    int max = a[0];
    for (int i =0;i < size;i++){
        int temp =0;
        for (int j = i; j < size;j++){
            temp += a[j];
            if (max < temp){
                max = temp;
            }
        }
    }
    return max;
}
int main(){
    clock_t start = clock();
    int n;
    if (!(cin >> n) || n <= 0) return 0;    
    int a[n];
    int h = maxO2(a,n);
    cout<< h<<endl;
    clock_t end = clock();
    double time = static_cast<double>(end - start);
    if (time > 300) cout <<"TLN"<<endl;
    std::cout << "CPU time: " << time << " s\n";
}