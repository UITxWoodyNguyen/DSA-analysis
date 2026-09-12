#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> sizes = {100, 1000, 10000, 100000, 150000, 200000, 300000, 500000, 600000, 700000, 800000, 900000, 1000000, 10000000};

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(-1000, 1000);

    for (int N : sizes) {
        string filename = "testcase/input/test" + to_string(N) + ".inp";
        ofstream fout(filename);
        if (!fout) {
            cerr << "Khong the tao file " << filename << "\n";
            continue;
        }

        fout << N << "\n";
        for (int i = 0; i < N; ++i) {
            fout << dist(rng);
            if (i + 1 < N) fout << ' ';
        }
        fout << "\n";

        cout << "Da sinh " << filename << " voi N = " << N << "\n";
    }

    cout << "Hoan tat sinh tat ca file test.\n";
    return 0;
}