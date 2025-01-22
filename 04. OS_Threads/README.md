# Practical Work 4 - Operating Systems (Multithreaded Implementation)

Operating Systems - **Multithreaded Matrix Multiplication**  <br>
Vinicius Giovani MOREIRA NASCIMENTO  

## Overview
This project implements matrix multiplication using **POSIX threads (Pthreads)** in a Unix-based system. It explores multithreading to improve computation performance and highlights the management of shared resources among threads.

Key concepts:
- Threading and synchronization.
- Matrix manipulation in memory.
- Performance comparison between single-threaded and multi-threaded approaches.

---

## Execution 

### To compile the project, open a terminal in the `tp04` folder and type:  
    make  

### Run the matrix multiplication with:
    ./bin/matrix_product
    
### Clean Generated Files:
    make clean
    
To remove object files and executables

---

## Components

### 1. Program **matrix.h**
Location: `include/matrix.h`  
Header file defining the matrix structure and function prototypes:
- `matrix_t`: Represents a matrix with rows, columns, and a pointer to the data.
- `args_t`: Arguments passed to threads during multi-threaded computation.

#### Function Categories:
- Mono-thread functions (`mono_thread`, `product_matrix`).
- Multi-thread functions (`multi_thread`, `product_matrix_thread`).
- Utility functions (`init_matrix`, `fill_matrix`, `print_matrix`, etc.).

### 2. Program **matrix_product.c**
Location: `src/matrix_product.c`

Main implementation of matrix multiplication:

- Mono-threaded Computation: Calculates the product of two matrices sequentially.
- Multi-threaded Computation: Splits the task into sub-matrices processed by multiple threads. Each thread operates on a defined subset of rows to balance workload.

#### Key Concepts:
- **Filtering by Processes**: Each process is responsible for filtering multiples of one prime number.
- **Pipeline**: Chain of processes implemented using anonymous pipes.
- **Synchronization**: Use of `fork()` and termination signals.
- **Shared File**: `fflush()` is used to synchronize writes to the file.

### 3. Program **main.c**
Location: `src/main.c`

Main entry point of the program:

- **Parameter Parsing**: Handles command-line arguments to set the number of threads and matrix size or run automated tests.
- **Matrix Initialization**: Creates and fills matrices with random values for computation.
- **Mono-threaded Execution**: Calls the mono-thread function to compute the matrix product sequentially.
- **Multi-threaded Execution**: Calls the multi-thread function to compute the matrix product using the specified number of threads.
- **Automated Tests**: Executes multiple configurations to evaluate performance under different matrix sizes and thread counts.

#### Key Concepts:
- **Dynamic Thread Management**: Adjusts the number of threads dynamically based on user input.
- **Matrix Operations**: Initializes, prints, and processes matrices with configurable sizes.
- **Performance Measurement**: Tracks execution time for mono-threaded and multi-threaded computations.
- **Test Automation**: Provides functionality to test matrix multiplication across various scenarios.

#### Workflow:
1. The program initializes two matrices filled with random values.
2. It computes the matrix product:
    - Mono-thread: Sequential multiplication.
    - Multi-thread: Work is divided among threads, each computing a subset of rows.
3. Results and execution times are displayed in the terminal.
4. (Optional) Automated tests are performed with predefined matrix sizes and thread counts.

---

## Features
- Single-threaded Approach
    - Uses the `mono_thread` function to calculate the product matrix sequentially.
    - Measures execution time using `clock_t` and `time_t`.
- Multi-threaded Approach
    - Dynamically creates threads based on system capabilities.
    - Threads are managed with Pthreads (`pthread_create`, `pthread_join`).
    - Threads operate independently on defined segments of the result matrix.
    - Demonstrates improved execution time for large matrices.

---

## Example Output

### Terminal Output
```bash
Using 4 thread(s).

Matrix m1
10.00 11.00 12.00
13.00 14.00 15.00
16.00 17.00 18.00

Matrix m2
19.00 20.00 21.00
22.00 23.00 24.00
25.00 26.00 27.00

======== Mono Thread ========
Clock_t -> 1000.000 ticks (1.234 seconds)
Time_t  -> 1.234 seconds

======== Multi Threads ========

Clock_t -> 500.000 ticks (0.567 seconds)
Time_t  -> 0.567 seconds

```

### When executed with automated tests (-E flag):
```bash
./bin/matrix_product -E

=== Testing matrix 10x10 with 4 thread(s) ===

Mono Thread:
Clock_t -> 10.000 ticks (0.002 seconds)
Time_t  -> 0.002 seconds

Multi Thread:
Clock_t -> 5.000 ticks (0.001 seconds)
Time_t  -> 0.001 seconds

...

=== Testing matrix 1000x1000 with 4 thread(s) ===

Mono Thread:
Clock_t -> 100000.000 ticks (12.345 seconds)
Time_t  -> 12.345 seconds

Multi Thread:
Clock_t -> 50000.000 ticks (6.789 seconds)
Time_t  -> 6.789 seconds
```

---

## Observations
- **Part of this code was provided by ENSICAEN; don't forget to mention that!**
- For more informations about the project, read the file in `./doc` folder
- Performance Testing: Use different matrix sizes (10x10, 100x100, etc.) to evaluate speedup.
- The constant `PRINT` can be set to `0` for faster execution without matrix display.
- Thread Count: Modify `THREAD_DEFAULT` in `matrix.h` to control the default number of threads.
- The program dynamically adjusts based on the number of available CPU cores.
- Memory Management: Properly allocates and frees memory to avoid leaks.