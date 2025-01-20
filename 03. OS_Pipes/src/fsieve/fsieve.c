#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "../../include/fsieve.h"
#define INPUT 1	
#define OUTPUT 0

void manage_parent(int pipes[2], int MAX_VALUE) {
    printf("Parent process (PID %d)\n", getpid());

    close(pipes[OUTPUT]);

    for (int i = 2; i <= MAX_VALUE; i++) {
        write(pipes[INPUT], &i, sizeof(int));
        printf("%d sent\n", i);
    }

    int end_signal = -1;
    write(pipes[INPUT], &end_signal, sizeof(int));
    close(pipes[INPUT]);

    wait(NULL);
    printf("Parent: has received child termination.\n");
}

void manage_childs(int received_pipes[2], int pipe_index, int responsability) {
    printf("Child process (PID %d) handling pipe %d with responsibility %d\n", getpid(), pipe_index, responsability);
    int create_child = 0;

    close(received_pipes[INPUT]); 
    save_primes(responsability); 

    int next_pipe[2];
    if (pipe(next_pipe) == -1) { 
        handle_fatal_error("Error creating next pipe.\n");
    }

    int number;
    while (read(received_pipes[OUTPUT], &number, sizeof(int)) > 0) {
        if (number == -1) {
            write(next_pipe[INPUT], &number, sizeof(int));
            break;
        }

        if (number % responsability != 0) {
            if (create_child == 0) {
                create_child = 1;

                pid_t pid = fork();
                if (pid == -1) { handle_fatal_error("Error forking child.\n");}

                if (pid == 0) {
                    close(next_pipe[INPUT]);
                    manage_childs(next_pipe, pipe_index + 1, number);
                }
            }
            write(next_pipe[INPUT], &number, sizeof(int));
        }
    }

    close(next_pipe[INPUT]);
    close(received_pipes[OUTPUT]);

    wait(NULL);
    exit(EXIT_SUCCESS);
}


void save_primes(int prime) {
    char path[] = "./primes.txt";
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        handle_fatal_error("Error opening file.\n");
    }
    fprintf(file, "%d\n", prime);
    fclose(file);
}

void handle_fatal_error(const char *message) {
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}