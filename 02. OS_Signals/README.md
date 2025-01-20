# Practical Work 2 - Operating Systems (Periodic Data Generation)

Operating Systems - **Sine and Cosine Generator**  <br>
Vinicius Giovani MOREIRA NASCIMENTO  

## Overview
This project explores the concept of **process communication** in Operating Systems using POSIX signals (`sigaction`). It involves the creation, execution, and synchronization of multiple processes to calculate and visualize periodic data. The program generates sine and cosine values incrementally, logs the results to files, and plots them using Gnuplot.

---

## Execution 

### To compile the project, open a terminal in the `tp02` folder and type:  
    make  

### To run the program with data generation and plotting:  
    ./bin/sin_cos  

### To remove object files and the executable, type:  
    make clean  

---

## Components

### 1. `main.c`
This is the core of the program, handling process management and signal communication:
- **Parent Process**: 
  - Sets up signal handlers for `SIGALRM` and `SIGUSR1`.
  - Manages process termination and restarts for plotting.
- **Child Processes**: 
  - Calculate sine and cosine values for angles incremented by 10°.
  - Log the results to `sinus.txt` and `cosinus.txt`.

#### Key Concepts:
- **POSIX Signals**: Implements signal handling using `sigaction`.
- **Process Synchronization**: Uses signals to coordinate parent-child interaction.
- **Dynamic Process Management**: Creates new processes for Gnuplot visualization upon data generation completion.

---

### 2. `sin_cos.c`
This module handles the computation and logging of sine and cosine values:
- Converts angles from degrees to radians.
- Computes sine (`sin`) or cosine (`cos`) based on process type.
- Logs data to text files in a format compatible with Gnuplot.

#### Key Concepts:
- **Trigonometric Calculations**: Implements mathematical computations for periodic functions.
- **Data Logging**: Saves angle-value pairs to `sinus.txt` and `cosinus.txt`.

---

### 3. `sin_cos_g.c`
This program manages the visualization of sine and cosine data:
- Executes Gnuplot commands to plot the data.
- Automatically generates graphs for sine and cosine functions from the log files.

#### Key Concepts:
- **Gnuplot Integration**: Uses `execlp` to execute Gnuplot commands.
- **File Handling**: Reads data files (`sinus.txt` and `cosinus.txt`) for plotting.

---

## Features
- **Signal Handling**: Implements `SIGALRM` for periodic execution and `SIGUSR1` for process coordination.
- **Sine and Cosine Calculations**: Calculates values incrementally every second.
- **Data Visualization**: Automatically generates plots for the sine and cosine functions using Gnuplot.

---

## Example Output

### Terminal Output
Child 1 (1234): sinus(0) = 0.00 <br>
Child 2 (1235): cosinus(0) = 1.00 <br>
Child 1 (1234): sinus(10) = 0.17 <br>
Child 2 (1235): cosinus(10) = 0.98 <br>
...

### Data Files
- **`sinus.txt`**: 0.0 0.0 10.0 0.17 20.0 0.34 ... <br>
- **`cosinus.txt`**: 0.0 1.0 10.0 0.98 20.0 0.94 ... <br>

---

## Observations
- Ensure Gnuplot is installed and accessible via the system PATH to generate graphs.
- Generated graphs will display smooth curves for sine and cosine functions.
- For more informations about the project, read the file in `./doc` folder