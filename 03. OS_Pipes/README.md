# Practical Work 3 - Operating Systems (Pipeline Prime Numbers)

Operating Systems - **Filtering through Anonymous Pipes**  <br>
Vinicius Giovani MOREIRA NASCIMENTO  

## Overview
This project explores **interprocess communication** in Operating Systems using **anonymous pipes**. The goal is to implement a **filtering pipeline**, where each child process calculates a specific prime number and filters all its multiples. The final result is saved in a text file named `prime_numbers.txt`.
- **Simple:** A basic example of data transmission between parent and child processes.
- **Fsieve:** Full implementation of the filtering pipeline for prime number calculation.

---

## Project Structure
. <br>
├── Makefile <br>
├── README.md <br>
├── bin <br>
│   ├── fsieve <br>
│   └── simple <br>
├── include <br>
│   └── fsieve.h <br>
├── src <br>
    ├── fsieve <br>
    │   ├── fsieve.c <br>
    │   └── main.c <br>
    └── simple <br>
        └── main.c <br>

---

## Execution 

### To compile the project, open a terminal in the `tp03` folder and type:  
    make  

### To test communication between processes:
    ./bin/simple -m <MAX_VALUE>
    
Replace <MAX_VALUE> with the desired maximum value. If no value is provided, the default is 100.

### Run the Fsieve Program to calculate prime numbers:
    ./bin/fsieve -m <MAX_VALUE>
    
Replace <MAX_VALUE> with the upper limit for prime numbers.

### Clean Generated Files:
    make clean
    
To remove object files and executables

---

## Components

### 1. Program **Simple**
Location: `src/simple/main.c`  
The **Simple** program demonstrates basic communication between a parent process and its child:
- The parent sends a sequence of integers through an anonymous pipe.
- The child receives and prints the values until encountering the termination signal (`-1`).

#### Key Commands:
- **Pipe Creation**: `pipe()`
- **Data Transmission**: `write()`
- **Data Reception**: `read()`

### 2. Program **Fsieve**
Location: `src/fsieve/`

The **Fsieve** program implements the filtering algorithm:
- The parent creates an initial child process that filters the first prime number.
- Each subsequent child process creates its own child to handle the next prime number.
- Prime numbers are saved in the file `prime_numbers.txt`.

#### Key Concepts:
- **Filtering by Processes**: Each process is responsible for filtering multiples of one prime number.
- **Pipeline**: Chain of processes implemented using anonymous pipes.
- **Synchronization**: Use of `fork()` and termination signals.
- **Shared File**: `fflush()` is used to synchronize writes to the file.

#### Workflow:
1. The parent sends a sequence of integers to the first child.
2. The child saves the prime number and filters multiples.
3. The process continues until all numbers have been processed.

---

## Features
- **Signal Handling**: Implements `SIGALRM` for periodic execution and `SIGUSR1` for process coordination.
- **Pipeline Filtering**: Dynamically creates child processes to filter prime numbers and their multiples.
- **Data Logging**: Saves prime numbers in the `prime_numbers.txt` file for further analysis.

---

## Example Output

### Terminal Output
```bash
Parent process (PID 1234)
0 sent
1 sent
...
Child process (PID 1235)
0 received
1 received
...
Child process terminating.
```

### File prime_numbers.txt (Fsieve)
```bash
2
3
5
7
11
13
... 
```

---

## Observations
- For more informations about the project, read the file in `./doc` folder
- Ensure the fflush() function is used after each write to the prime_numbers.txt file to avoid inconsistencies.
- The maximum limit for values is defined in MAX_LIMIT, and the default is 100 if no argument is passed.
- The Fsieve program saves prime numbers in ascending order in the file prime_numbers.txt.