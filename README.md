# DSA-analysis

Comparison of maximum subarray sum algorithms with different time complexities: O(n³), O(n²), O(n log n), and O(n).

## Features

- **O(n³)** — Brute force triple nested loop (`src/max_subsequence_On3.cpp`)
- **O(n²)** — Optimized brute force with running sum (`src/BigO2.cpp`)
- **O(n log n)** — Divide and conquer approach (`src/BigOnLogN.cpp`)
- **O(n)** — Kadane's algorithm (`src/On-kadane.cpp`)
- **Test generator** — Creates input files of varying sizes (100 to 10,000,000 elements) in `testcase/input/`
- **Test runner** — Python script to run all algorithms on all test cases with 60s timeout

## Installation

Requires a C++ compiler (g++ recommended) and Python 3.

```bash
# Clone the repository
git clone <repo-url>
cd DSA-analysis
```

## Quick Start

Compile all algorithms:

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

Timeout is 60 seconds. TLE cases show:
```
Time Limit Exceeded (TLE)
Runtime: 60000.00 ms
```

## Algorithm Complexity Comparison

| Algorithm | Time Complexity | Space Complexity | Source File | Binary |
|-----------|----------------|------------------|-------------|--------|
| Brute Force (3 loops) | O(n³) | O(1) | `max_subsequence_On3.cpp` | `on3.exe` |
| Optimized Brute Force | O(n²) | O(1) | `BigO2.cpp` | `on2.exe` |
| Divide & Conquer | O(n log n) | O(log n) | `BigOnLogN.cpp` | `onlogn.exe` |
| Kadane's Algorithm | O(n) | O(1) | `On-kadane.cpp` | `kadane.exe` |

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

## Project Structure

```
DSA-analysis/
├── src/
│   ├── max_subsequence_On3.cpp   # O(n³) brute force
│   ├── BigO2.cpp                 # O(n²) optimized
│   ├── BigOnLogN.cpp             # O(n log n) divide & conquer
│   └── On-kadane.cpp             # O(n) Kadane's algorithm
├── exe/                          # Compiled binaries
│   ├── on3.exe
│   ├── on2.exe
│   ├── onlogn.exe
│   └── kadane.exe
├── testcase/
│   ├── testGenerate.cpp          # Test case generator
│   ├── testGenerate.exe          # Compiled generator (Windows)
│   ├── run_tests.py              # Test runner script
│   ├── input/                    # Generated test files
│   └── output/                   # Test results
│       ├── BigOn3/
│       ├── BigO2/
│       ├── BigOnLogN/
│       └── BigOn/
└── README.md
```

## License

This project is for educational purposes (DSA assignment).