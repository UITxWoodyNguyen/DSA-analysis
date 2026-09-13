# DSA-analysis

Comparison of maximum subarray sum algorithms with different time complexities: O(n³), O(n²), O(n log n), and O(n).

## Features

- **O(n³)** — Brute force triple nested loop (`src/max_subsequence_On3.cpp`)
- **O(n²)** — Optimized brute force with running sum (`src/BigO2.cpp`)
- **O(n log n)** — Divide and conquer approach (`src/BigOnLogN.cpp`)
- **O(n)** — Kadane's algorithm (`src/On-kadane.cpp`)
- **Test generator** — Creates input files of varying sizes (100 to 10,000,000 elements) in `testcase/input/`

## Installation

Requires a C++ compiler (g++ recommended).

```bash
# Clone the repository
git clone <repo-url>
cd DSA-analysis
```

## Quick Start

Compile any algorithm:

```bash
g++ src/On-kadane.cpp -o kadane -O2
```

Run with a test input:

```bash
./kadane < testcase/input/test1000.inp
```

## Usage

Each algorithm reads from stdin:
1. First line: integer `N` (array size)
2. Second line: `N` space-separated integers

Output: maximum subarray sum

```bash
# Compile all algorithms
g++ src/max_subsequence_On3.cpp -o on3 -O2
g++ src/BigO2.cpp -o on2 -O2
g++ src/BigOnLogN.cpp -o onlogn -O2
g++ src/On-kadane.cpp -o kadane -O2

# Run on different test sizes
./kadane < testcase/input/test100000.inp
./on2 < testcase/input/test10000.inp
```

### Generate new test cases

```bash
g++ testcase/testGenerate.cpp -o testcase/testGenerate -O2
./testcase/testGenerate
```

This creates files in `testcase/input/test<N>.inp` for sizes: 100, 1000, 10000, 100000, 150000, 200000, 300000, 500000, 600000, 700000, 800000, 900000, 1000000, 10000000.

## Algorithm Complexity Comparison

| Algorithm | Time Complexity | Space Complexity | File |
|-----------|----------------|------------------|------|
| Brute Force (3 loops) | O(n³) | O(1) | `max_subsequence_On3.cpp` |
| Optimized Brute Force | O(n²) | O(1) | `BigO2.cpp` |
| Divide & Conquer | O(n log n) | O(log n) | `BigOnLogN.cpp` |
| Kadane's Algorithm | O(n) | O(1) | `On-kadane.cpp` |

## Testing

Run all algorithms on the same input to verify correctness:

```bash
# Example with small input
echo -e "5\n-2 1 -3 4 -1" | ./kadane
echo -e "5\n-2 1 -3 4 -1" | ./on2
echo -e "5\n-2 1 -3 4 -1" | ./onlogn
echo -e "5\n-2 1 -3 4 -1" | ./on3
# All should output: 4
```

## Project Structure

```
DSA-analysis/
├── src/
│   ├── max_subsequence_On3.cpp   # O(n³) brute force
│   ├── BigO2.cpp                 # O(n²) optimized
│   ├── BigOnLogN.cpp             # O(n log n) divide & conquer
│   └── On-kadane.cpp             # O(n) Kadane's algorithm
├── testcase/
│   ├── testGenerate.cpp          # Test case generator
│   ├── testGenerate.exe          # Compiled generator (Windows)
│   └── input/                    # Generated test files
└── README.md
```

## License

This project is for educational purposes (DSA assignment).