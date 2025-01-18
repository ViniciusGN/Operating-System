# Practical Work 1 - Operating Systems (Processes) 
Operating Systems - **Curve Generator** <br>
Vinicius Giovani MOREIRA NASCIMENTO  

## Overview
This project demonstrates the concept of **process management** in Operating Systems through practical implementations. It involves the creation, execution, and synchronization of multiple processes, showcasing their interaction and resource utilization. The project is divided into two main functionalities: plotting a mathematical graph using Gnuplot and running various tasks with child processes.

---

## Execution 

### To compile the project, open a terminal in the `tp01` folder and type:  
    make  

### To run the program with the default range [0, B], use:  
    ./build/plotter 50  

### To use the range [-B, B], add the `-i` parameter:  
    ./build/plotter 50 -i  

### To remove object files and the executable, type:  
    make clean  

### To open the requested PDF file (`01_tp-generation-courbe.pdf`) located in the `doc` folder, run the complementary program with:  
    ./build/complement ../doc/01_tp-generation-courbe.pdf  

---

## Components

### 1. `complement.c`
This program creates **four child processes** using `fork()` to execute different tasks simultaneously:
- **Child 1**: Opens Firefox with two tabs (URLs to specific resources).
- **Child 2**: Opens Firefox with a specific search query.
- **Child 3**: Opens a file in Gedit for text editing.
- **Child 4**: Opens the same file in Evince for PDF viewing.

The parent process waits for all child processes to complete using `wait(NULL)`.

#### Key Concepts:
- **Forking**: `fork()` is used to create child processes.
- **Exec family**: `execvp()` replaces the current process image with a new process.
- **Synchronization**: Parent waits for all children using `wait()`.

---

### 2. `iplot.c`
This module generates a Gnuplot script file (`commandes.gp`) to plot a graph of the **sinc function** (`sin(x)/x`). The user can define the range of the graph:
- Default: `[0, B]`
- Optional: `[-B, B]` (activated by the `-i` flag).

#### Key Concepts:
- **File Handling**: Creates a `.gp` script with commands for Gnuplot.
- **Dynamic Range**: Adjusts graph intervals based on user input.
- **Graph Plotting**: Uses `execlp()` to call Gnuplot for rendering the graph.

---

### 3. `main.c`
This program is the entry point for the plotting functionality. It:
1. Accepts user inputs (`B` and optional `-i`).
2. Calls `create_file` to generate the Gnuplot script.
3. Forks a child process to execute the `plot_data` function, which renders the graph using Gnuplot.

#### Key Concepts:
- **Parameter Handling**: Parses and adjusts behavior based on command-line arguments.
- **Process Creation**: Demonstrates parent-child process interaction.