# Operating Systems Practical Projects
Vinicius Nascimento <br>

This repository contains five practical projects designed to explore core concepts of Operating Systems, provided by classes at ENSICAEN and UnB. Each project delves into a specific topic, demonstrating its application through C programming and Unix system calls.

---

## Table of Contents

1. [Process Management and Curve Generation](#1-process-management-and-curve-generation)
2. [Periodic Data Generation and Signals](#2-periodic-data-generation-and-signals)
3. [Pipeline for Prime Number Calculation](#4-pipeline-for-prime-number-calculation)
4. [Multithreaded Matrix Multiplication](#3-multithreaded-matrix-multiplication)
5. [Shared Memory and Drink Dispenser Simulation](#5-shared-memory-and-drink-dispenser-simulation)

---

### 1. Process Management and Curve Generation

**Objective:**  
Learn process creation and management using `fork()` and `exec()` to plot mathematical functions with **Gnuplot**.

#### Key Features:
- Parent process dynamically creates command files for Gnuplot.
- Child processes execute Gnuplot to render plots (e.g., the sinc function).
- Introduces process synchronization using parent-child relationships.

### 2. Periodic Data Generation and Signals

**Objective:**  
Implement inter-process communication (IPC) using **POSIX signals** `(SIGALRM, SIGCHLD)` to coordinate data generation and visualization.

#### Key Features:
- Two child processes alternately calculate sine and cosine values of incremented angles.
- Outputs data to files for Gnuplot-compatible plots.
- Demonstrates signal handling for synchronization.

### 3. Pipeline for Prime Number Calculation

**Objective:**  
Implement a **pipeline mechanism** using anonymous pipes for inter-process communication to filter prime numbers.

#### Key Features:
- Processes communicate via pipes to filter and generate prime numbers.
- Results are stored in prime_numbers.txt.
- Demonstrates the efficiency of pipelines for sequential data processing.

### 4. Multithreaded Matrix Multiplication

**Objective:**  
Utilize **POSIX threads** to perform matrix multiplication, distributing workload across multiple threads.

#### Key Features:
- Threads handle distinct portions of the result matrix.
- Supports large matrices for performance testing.
- Observes thread behavior using tools like htop.

### 5. Shared Memory and Drink Dispenser Simulation

**Objective:**  
Use **shared memory** to simulate the configuration panel of a drink dispenser.

#### Key Features:
- Simulates unlocking and controlling a drink dispenser using shared memory.
- Includes password decryption, valve activation, and drink selection.
- Demonstrates shared memory access and synchronization.

---

## Summary

These projects cover fundamental Operating Systems concepts:

- **Signals**: Utilizing POSIX signals for inter-process communication and synchronization.
- **File Management**: Managing and manipulating files for data input/output across processes.
- **Memory Management**: Implementing shared memory and handling memory allocation for inter-process resource sharing.
- **Message Queues**: Leveraging message queues for structured inter-process communication.
- **Synchronization**: Ensuring proper coordination and access control among concurrent processes and threads.

Feel free to explore, modify, and extend these implementations to deepen your understanding of Operating Systems.