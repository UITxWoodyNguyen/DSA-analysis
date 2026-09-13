<p align="center">
  <a href="https://www.uit.edu.vn/" title="Trường Đại học Công nghệ Thông tin" style="border: none;">
    <img src="https://i.imgur.com/WmMnSRt.png" alt="Trường Đại học Công nghệ Thông tin | University of Information Technology">
  </a>
</p>

<h1 align="center">DSA Analysis Assignment</h1>

---
**Author**:
- Nguyễn Minh Thành - ATTT2025.3 - 2552
- Nguyễn Công Tuấn - ATTT2025.3 - 2552
- Trần Lâm Nguyên - ATTT2025.2 - 2552

**Subject**: Data Structures and Algorithms (DSA) - IT003

**Class Code**: IT003.R14

---

**Purposes**: Comparison of maximum subarray sum algorithms with different time complexities: O(n³), O(n²), O(n log n), and O(n).

---

## Features

- **O(n³)** — Brute force triple nested loop (`src/max_subsequence_On3.cpp`)
- **O(n²)** — Optimized brute force with running sum (`src/BigO2.cpp`)
- **O(n log n)** — Divide and conquer approach (`src/BigOnLogN.cpp`)
- **O(n)** — Kadane's algorithm (`src/On-kadane.cpp`)
- **Test generator** — Creates input files of varying sizes (100 to 10,000,000 elements) in `testcase/input/`
- **Test runner** — Python script to run all algorithms on all test cases with 60s timeout, detects Stack Overflow and TLE

## Installation

Requires a C++ compiler (g++ recommended) and Python 3.

```bash
# Clone the repository
git clone <repo-url>
cd DSA-analysis
```

## Quick Start

Compile all algorithms (outputs to `exe/` folder):

```bash
g++ src/max_subsequence_On3.cpp -o exe/on3.exe -O2
g++ src/BigO2.cpp -o exe/on2.exe -O2
g++ src/BigOnLogN.cpp -o exe/onlogn.exe -O2
g++ src/On-kadane.cpp -o exe/kadane.exe -O2
```

Run with a test input:

```bash
./exe/kadane.exe < testcase/input/test1000.inp
```

## Usage

Each algorithm reads from stdin:
1. First line: integer `N` (array size)
2. Second line: `N` space-separated integers

Output: maximum subarray sum

### Generate test cases

```bash
g++ testcase/testGenerate.cpp -o testcase/testGenerate.exe -O2
./testcase/testGenerate.exe
```

This creates files in `testcase/input/test<N>.inp` for sizes: 100, 1000, 10000, 100000, 150000, 200000, 300000, 500000, 600000, 700000, 800000, 900000, 1000000, 10000000.

### Run tests

```bash
python testcase/run_tests.py
```

Select algorithm:
- `1` — O(n³) Brute Force
- `2` — O(n²) Optimized
- `3` — O(n log n) Divide & Conquer
- `4` — O(n) Kadane's Algorithm
- `5` — Run ALL algorithms

Results are saved in `testcase/output/<BigO>/` with format:
```
<result>
Runtime: <ms>
```

Timeout is 60 seconds. Special cases:
- **TLE**: `Time Limit Exceeded (TLE)` + `Runtime: 60000.00 ms`
- **Stack Overflow**: `Stack Overflow` + runtime when process crashes
## Runtime Measurement in C++

The benchmark implementation in `maxSubArr.cpp` uses `<chrono>` for high-resolution timing:

```cpp
#include <chrono>
using namespace std::chrono;

auto start = high_resolution_clock::now();
// ... algorithm code ...
auto end = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(end - start).count();
cout << "Runtime: " << duration << " ms\n";
```

Key points:
- **`high_resolution_clock`** — Best available clock (typically nanosecond precision)
- **`duration_cast<milliseconds>`** — Converts to milliseconds
- **Measures wall-clock time** — Includes all CPU work, memory access, I/O overhead
- **Single-threaded** — All algorithms run sequentially in one thread

### Measurement Approaches Used

| File | Approach |
|------|----------|
| `maxSubArr.cpp` | In-class timing: `high_resolution_clock::now()` before/after each method |
| `testcase/run_tests.py` | External timing: Python `time.perf_counter()` around subprocess |
| `solution.cpp` | No timing — pure algorithm output |

### Stack Overflow Detection

The Python runner detects crashes via:
1. Non-zero exit code from subprocess
2. Empty stdout output
3. Reports as `Stack Overflow` in output files

## Algorithm Complexity Comparison

| Algorithm | Time Complexity | Space Complexity | Source File | Binary |
|-----------|----------------|------------------|-------------|--------|
| Brute Force (3 loops) | O(n³) | O(1) | `max_subsequence_On3.cpp` | `exe/on3.exe` |
| Optimized Brute Force | O(n²) | O(1) | `BigO2.cpp` | `exe/on2.exe` |
| Divide & Conquer | O(n log n) | O(log n) | `BigOnLogN.cpp` | `exe/onlogn.exe` |
| Kadane's Algorithm | O(n) | O(1) | `On-kadane.cpp` | `exe/kadane.exe` |

## Implementation Notes

- All algorithms use **dynamic allocation** (`new int[n]`) instead of VLAs to avoid stack overflow on large inputs (1M+ elements)
- Test runner detects non-zero exit codes and empty output as **Stack Overflow**
- Test binaries are compiled to and run from `exe/` folder

## Testing

Run all algorithms on the same input to verify correctness:

```bash
# Example with small input
echo "5 -2 1 -3 4 -1" | exe/on3.exe
echo "5 -2 1 -3 4 -1" | exe/on2.exe
echo "5 -2 1 -3 4 -1" | exe/onlogn.exe
echo "5 -2 1 -3 4 -1" | exe/kadane.exe
# All should output: 4
```

Test with all-negative array:
```bash
echo "3 -5 -2 -3" | exe/kadane.exe
# Output: -2
```

## Additional Files

| File | Purpose |
|------|---------|
| `maxSubArr.cpp` | Single class with all 4 algorithms + internal runtime measurement |
| `solution.cpp` | Combined 4 functions, no timing, reads stdin, outputs 4 results |
| `result-comparing/resultComparing.cpp` | Parses all `.out` files, compares results & runtimes |
## Test Results Summary (60s timeout)

| Input Size | O(n³) | O(n²) | O(n log n) | O(n) |
|------------|-------|-------|------------|------|
| 100 | ✓ | ✓ | ✓ | ✓ |
| 1,000 | ✓ | ✓ | ✓ | ✓ |
| 10,000 | TLE | ✓ | ✓ | ✓ |
| 100,000 | TLE | ✓ | ✓ | ✓ |
| 1,000,000 | TLE | TLE | ✓ | ✓ |
| 10,000,000 | TLE | TLE | TLE | ✓ |

## Project Structure

```
DSA-analysis/
├── src/
│   ├── max_subsequence_On3.cpp   # O(n³) brute force
│   ├── BigO2.cpp                 # O(n²) optimized
│   ├── BigOnLogN.cpp             # O(n log n) divide & conquer
│   └── On-kadane.cpp             # O(n) Kadane's algorithm
├── exe/                          # Compiled binaries (gitignored)
│   ├── on3.exe
│   ├── on2.exe
│   ├── onlogn.exe
│   └── kadane.exe
├── testcase/
│   ├── testGenerate.cpp          # Test case generator
│   ├── testGenerate.exe          # Compiled generator (Windows)
│   ├── run_tests.py              # Test runner script
│   ├── input/                    # Generated test files (gitignored)
│   └── output/                   # Test results (gitignored)
│       ├── BigOn3/
│       ├── BigO2/
│       ├── BigOnLogN/
│       └── BigOn/
├── result-comparing/
│   ├── resultComparing.cpp       # Comparison tool
│   ├── resultComparing.exe       # Compiled (gitignored)
│   └── result.txt                # Output comparison (gitignored)
├── maxSubArr.cpp                 # Combined class with timing
├── maxSubArr.exe                 # Compiled (gitignored)
├── solution.cpp                  # Combined functions, no timing
├── solution.exe                  # Compiled (gitignored)
├── .gitignore
└── README.md
```

## License

This project is for educational purposes (DSA assignment).