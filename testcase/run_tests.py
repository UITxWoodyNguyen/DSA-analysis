import os
import subprocess
import time
import sys
import platform
from pathlib import Path

IS_WINDOWS = platform.system() == 'Windows'

ALGORITHMS = {
    '1': {'name': 'BigOn3', 'source': 'src/max_subsequence_On3.cpp', 'binary': 'on3', 'timeout': 60},
    '2': {'name': 'BigO2', 'source': 'src/BigO2.cpp', 'binary': 'on2', 'timeout': 60},
    '3': {'name': 'BigOnLogN', 'source': 'src/BigOnLogN.cpp', 'binary': 'onlogn', 'timeout': 60},
    '4': {'name': 'BigOn', 'source': 'src/On-kadane.cpp', 'binary': 'kadane', 'timeout': 60},
}

BASE_DIR = Path(__file__).parent.parent
INPUT_DIR = BASE_DIR / 'testcase' / 'input'
OUTPUT_BASE = BASE_DIR / 'testcase' / 'output'

def get_binary_path(name):
    return BASE_DIR / 'exe' / f"{name}.exe" if IS_WINDOWS else BASE_DIR / 'exe' / name

def compile_algorithm(algo_info):
    binary_path = get_binary_path(algo_info['binary'])
    source_path = BASE_DIR / algo_info['source']
    binary_path.parent.mkdir(parents=True, exist_ok=True)
    result = subprocess.run(
        ['g++', str(source_path), '-o', str(binary_path), '-O2'],
        capture_output=True, text=True,
        cwd=str(BASE_DIR)
    )
    if result.returncode != 0:
        print(f"Compilation failed for {algo_info['name']}:")
        print(result.stderr)
        return False
    return True

def run_algorithm(algo_info, input_file):
    binary_path = get_binary_path(algo_info['binary'])
    if not binary_path.exists():
        print(f"Binary {binary_path.name} not found. Compile first.")
        return None, None

    try:
        start = time.perf_counter()
        with open(input_file, 'r') as f:
            result = subprocess.run(
                [str(binary_path)],
                stdin=f,
                capture_output=True,
                text=True,
                timeout=algo_info['timeout']
            )
        elapsed_ms = (time.perf_counter() - start) * 1000
        output = result.stdout.strip()
        
        if result.returncode != 0:
            return "Stack Overflow", elapsed_ms
        if not output:
            return "Stack Overflow", elapsed_ms
            
        return output, elapsed_ms
    except subprocess.TimeoutExpired:
        return "Time Limit Exceeded (TLE)", algo_info['timeout'] * 1000
    except Exception as e:
        return f"Error: {e}", None

def process_algorithm(choice):
    algo = ALGORITHMS[choice]
    algo_name = algo['name']
    output_dir = OUTPUT_BASE / algo_name
    output_dir.mkdir(parents=True, exist_ok=True)

    print(f"\n=== Running {algo_name} ===")
    if not compile_algorithm(algo):
        return

    input_files = sorted(INPUT_DIR.glob('test*.inp'))
    if not input_files:
        print("No input files found in testcase/input/")
        return

    for inp_file in input_files:
        out_file = output_dir / inp_file.name.replace('.inp', '.out')
        print(f"Processing {inp_file.name}...")

        result, runtime_ms = run_algorithm(algo, inp_file)

        with open(out_file, 'w') as f:
            if result and not result.startswith("Time Limit Exceeded") and not result.startswith("Error"):
                f.write(f"{result}\n")
            else:
                f.write(f"{result}\n")
            if runtime_ms is not None:
                f.write(f"Runtime: {runtime_ms:.2f} ms\n")
            else:
                f.write("Runtime: N/A\n")

        print(f"  -> {out_file.name} (Runtime: {runtime_ms:.2f} ms)" if runtime_ms else f"  -> {out_file.name}")

    print(f"\nCompleted {algo_name}. Outputs in {output_dir}")

def main():
    print("DSA Algorithm Test Runner")
    print("=" * 40)
    print("Select algorithm to run:")
    print("  1. O(n^3)    - Brute Force (max_subsequence_On3.cpp)")
    print("  2. O(n^2)    - Optimized (BigO2.cpp)")
    print("  3. O(n log n)- Divide & Conquer (BigOnLogN.cpp)")
    print("  4. O(n)      - Kadane's Algorithm (On-kadane.cpp)")
    print("  5. Run ALL algorithms")
    print("  0. Exit")
    print("=" * 40)

    choice = input("Enter choice [0-5]: ").strip()

    if choice == '0':
        return
    elif choice == '5':
        for c in ['1', '2', '3', '4']:
            process_algorithm(c)
    elif choice in ALGORITHMS:
        process_algorithm(choice)
    else:
        print("Invalid choice")

if __name__ == '__main__':
    main()