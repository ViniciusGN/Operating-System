# Practical Work 5 - Operating Systems (Shared Memory)
Operating Systems - **Drinks Dispenser Monitor**  
Vinicius Giovani MOREIRA NASCIMENTO  

---

## Overview
This project involves accessing and interacting with the shared memory of a drinks dispenser system. The program, **monitor**, manipulates the configuration panel of the dispenser to unlock, select drinks, and control the valve to pour the chosen beverage.

### Objectives:
- Understand inter-process communication through shared memory.
- Implement a program to interact with the dispenser's control panel.
- Demonstrate synchronization and data exchange via shared memory.

---

## Execution

### Compile the Program
```bash
make
```

### Compile the Program
```bash
./monitor
```

## Components

### 1. Program **monitor.c**
Location: `src/monitor.c`  
Main implementation for interacting with the dispenser:

- **Shared Memory Access:** Connects to the dispenser's shared memory segment.
- **Configuration Update:** Writes the correct encrypted password and modifies panel settings.
- **Valve Control:** Opens or closes the valve to pour drinks.
- **Drink Selection:** Allows users to choose a beverage.

#### Key Concepts:
- **Shared Memory Interaction:** Uses `shm_open`, `mmap`, and `msync` to access and modify shared memory.
- **Synchronization:** Ensures data consistency with proper memory syncing.
- **Custom Configuration:** Dynamically updates the dispenser's settings, such as valve state and selected drink.
- 

---

## Features
- **Shared Memory Access**
    - Uses `shm_open`, `mmap`, and `msync` to interact with the shared memory of the dispenser.
    - Ensures consistent synchronization during read and write operations.
- **Valve Control and Drink Selection**
    - Provides functionality to open or close the valve.
    - Allows the user to select the desired drink from the dispenser.
- **Password Management**
    - Implements a Caesar cipher decoder to decrypt the password.
    - Writes the correct password to unlock the dispenser.

---

## Example Output

### Initial State
```bash
ID: 12345
Shutdown status: 0
Valve: closed
Drink: none
```

### Updating Configuration
```bash
Valve set to: opened
Selected drink: water
```

### Resetting Configuration
```bash
Configuration reset to default.
Valve: closed
Drink: water
```

---

## Questions and Observations

### 1. What is the shared memory name on your system?
```bash
ls -lrt /dev/shm
```
Output:
```bash
-rw-r----- 1 user group 776 ... saperlipopette
```

### 2. What is the name of the semaphore used by the dispenser?
```bash
sem.saperlipopette-sem
```

### 3. What is the encrypted password?
```bash
root@DESKTOP-XXXXX:$PATH/OS_tp5_Moreira-Nascimento# cat /dev/shm/saperlipopette
Znaba qrf fbheprfopendwaterroot@DESKTOP-XXXXX:$PATH/OS_tp5_Moreira-Nascimento#
```
Separated strings:

```bash
Znaba qrf fbheprfopendwater
Znaba qrf fbheprf 
opened
water
```

Using the **Caesar cipher** is the easiest to decipher, because there are only **26 possibilities** of decryption. In this case, the key is **k = 13**, which gives the title of the novel by **Marcel Pagnol**, entitled `Manon des sources`.

---

## Observations

- **Part of this code was provided by ENSICAEN; the file `syrup_drink_dispenser` is proprietary to the institution and is not included in the project files.**
- Ensure the shared memory segment `/saperlipopette` exists and is accessible on your system.
- For additional details about the project, refer to the file in the `./doc` folder.
- Properly handle memory mappings and synchronization to avoid potential issues.