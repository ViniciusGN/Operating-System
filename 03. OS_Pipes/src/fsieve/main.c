#include <stdio.h>	
#include <unistd.h>	
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>	
#include <sys/types.h>	
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>
#include "../../include/fsieve.h"
#define INPUT 1	
#define OUTPUT 0
#define DEFAULT_VALUE 100
#define MAX_LIMIT 2000
#define MIN_LIMIT 100
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int process_arguments(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        char *endptr;
        long value = strtol(argv[2], &endptr, 10);

        if(*endptr == '\0') {
            if(value > MAX_LIMIT) { return MAX_LIMIT;}
            else if(value < MIN_LIMIT) { return MIN_LIMIT;}
            else{return (int)value;}
        }
        else { printf("Warning: The value after -m is not a valid number. Using default value %d.\n", DEFAULT_VALUE);}
    } else if(argc > 1) {printf("Incorrect usage. Using default value %d.\n", DEFAULT_VALUE);}

    printf("Using default value %d.\n", DEFAULT_VALUE);
    return DEFAULT_VALUE;
}

int main(int argc, char *argv[]) {
    clear_screen();

    int MAX_VALUE = process_arguments(argc, argv);
    int anonymous_pipe[2];

    if (pipe(anonymous_pipe) == -1) {
        handle_fatal_error("Error creating pipes.\n");
    }

    pid_t pid = fork();
    if (pid == -1) {
        handle_fatal_error("Error using fork().\n");
    }

    if (pid == 0) {
        manage_childs(anonymous_pipe, 1, 2);
    } else {
        manage_parent(anonymous_pipe, MAX_VALUE);
    }

    return EXIT_SUCCESS;
}