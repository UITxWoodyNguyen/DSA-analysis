#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <filesystem>
using namespace std;
using namespace filesystem;

struct Result {
    long long value;
    double runtime_ms;
    bool is_tle;
    bool is_stack_overflow;
    bool valid;
};

Result parseOutputFile(const string& filepath) {
    Result r = {0, 0, false, false, false};
    ifstream fin(filepath);
    if (!fin) return r;
    
    string line;
    vector<string> lines;
    while (getline(fin, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    fin.close();
    
    if (lines.empty()) return r;
    
    if (lines[0].find("Time Limit Exceeded") != string::npos) {
        r.is_tle = true;
        r.valid = true;
        if (lines.size() > 1 && lines[1].find("Runtime:") != string::npos) {
            size_t pos = lines[1].find("Runtime:");
            string num = lines[1].substr(pos + 8);
            num = num.substr(0, num.find("ms"));
            r.runtime_ms = stod(num);
        }
        return r;
    }
    
    if (lines[0].find("Stack Overflow") != string::npos) {
        r.is_stack_overflow = true;
        r.valid = true;
        if (lines.size() > 1 && lines[1].find("Runtime:") != string::npos) {
            size_t pos = lines[1].find("Runtime:");
            string num = lines[1].substr(pos + 8);
            num = num.substr(0, num.find("ms"));
            r.runtime_ms = stod(num);
        }
        return r;
    }
    
    try {
        r.value = stoll(lines[0]);
        r.valid = true;
    } catch (...) {
        return r;
    }
    
    if (lines.size() > 1 && lines[1].find("Runtime:") != string::npos) {
        size_t pos = lines[1].find("Runtime:");
        string num = lines[1].substr(pos + 8);
        num = num.substr(0, num.find("ms"));
        r.runtime_ms = stod(num);
    }
    
    return r;
}

int main() {
    string output_base = "testcase/output";
    vector<string> algos = {"BigOn3", "BigO2", "BigOnLogN", "BigOn"};
    vector<string> algo_names = {"O(n^3)", "O(n^2)", "O(n log n)", "O(n)"};
    
    map<string, vector<string>> input_files;
    for (const auto& entry : directory_iterator("testcase/input")) {
        if (entry.path().extension() == ".inp") {
            string name = entry.path().stem().string();
            if (name.rfind("test", 0) == 0) {
                string size_str = name.substr(4);
                input_files[size_str].push_back(entry.path().filename().string());
            }
        }
    }
    
    ofstream fout("result-comparing/result.txt");
    
    fout << setw(12) << "Size" 
         << setw(15) << "O(n^3)" 
         << setw(15) << "O(n^2)" 
         << setw(18) << "O(n log n)" 
         << setw(12) << "O(n)" 
         << "\n";
    fout << string(72, '=') << "\n";
    
    for (auto it = input_files.begin(); it != input_files.end(); ++it) {
        string size = it->first;
        fout << setw(12) << size;
        
        for (size_t i = 0; i < algos.size(); ++i) {
            string out_file = output_base + "/" + algos[i] + "/test" + size + ".out";
            Result r = parseOutputFile(out_file);
            
            if (!r.valid) {
                fout << setw(15) << "N/A";
            } else if (r.is_tle) {
                fout << setw(15) << "TLE";
            } else if (r.is_stack_overflow) {
                fout << setw(15) << "STACK_OVF";
            } else {
                fout << setw(15) << fixed << setprecision(2) << r.runtime_ms;
            }
        }
        fout << "\n";
    }
    
    fout << "\n\n=== Detailed Comparison ===\n\n";
    
    for (auto it = input_files.begin(); it != input_files.end(); ++it) {
        string size = it->first;
        fout << "--- N = " << size << " ---\n";
        
        for (size_t i = 0; i < algos.size(); ++i) {
            string out_file = output_base + "/" + algos[i] + "/test" + size + ".out";
            Result r = parseOutputFile(out_file);
            
            fout << "  " << setw(10) << algo_names[i] << ": ";
            if (!r.valid) {
                fout << "No output file\n";
            } else if (r.is_tle) {
                fout << "TLE (60000 ms)\n";
            } else if (r.is_stack_overflow) {
                fout << "Stack Overflow (" << fixed << setprecision(2) << r.runtime_ms << " ms)\n";
            } else {
                fout << "Result = " << r.value << ", Runtime = " << fixed << setprecision(2) << r.runtime_ms << " ms\n";
            }
        }
        fout << "\n";
    }
    
    fout << "\n=== Result Values Comparison ===\n\n";
    
    for (auto it = input_files.begin(); it != input_files.end(); ++it) {
        string size = it->first;
        bool first = true;
        long long expected = 0;
        bool all_match = true;
        int comparable_count = 0;
        
        for (size_t i = 0; i < algos.size(); ++i) {
            string out_file = output_base + "/" + algos[i] + "/test" + size + ".out";
            Result r = parseOutputFile(out_file);
            
            if (r.valid && !r.is_tle && !r.is_stack_overflow) {
                ++comparable_count;
                if (first) {
                    expected = r.value;
                    first = false;
                } else if (r.value != expected) {
                    all_match = false;
                }
            }
        }
        
        fout << "N = " << setw(10) << size << ": ";
        if (all_match && comparable_count >= 2) {
        } else {
            fout << "MISMATCH or missing\n";
            for (size_t i = 0; i < algos.size(); ++i) {
                string out_file = output_base + "/" + algos[i] + "/test" + size + ".out";
                Result r = parseOutputFile(out_file);
                if (r.valid && !r.is_tle && !r.is_stack_overflow) {
                    fout << "  " << algo_names[i] << ": " << r.value << "\n";
                }
            }
        }
    }
    
    fout.close();
    cout << "Comparison written to result-comparing/result.txt\n";
    return 0;
}