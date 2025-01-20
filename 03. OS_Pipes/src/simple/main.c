#include <stdio.h>	
#include <unistd.h>	
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>	
#include <sys/types.h>	
#include <sys/stat.h>
#include <sys/wait.h>
#define INPUT 1	
#define OUTPUT 0
#define DEFAULT_VALUE 1024
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

        if (*endptr == '\0') {
            if (value > MAX_LIMIT) {
                return MAX_LIMIT;
            } else if (value < MIN_LIMIT) {
                return MIN_LIMIT;
            } else {
                return (int)value;
            }
        } else {
            printf("Warning: The value after -m is not a valid number. Using default value %d.\n", DEFAULT_VALUE);
        }
    } else if (argc > 1) {
        printf("Incorrect usage. Using default value %d.\n", DEFAULT_VALUE);
    }

    printf("Using default value %d.\n", DEFAULT_VALUE);
    return DEFAULT_VALUE;
}

void handle_fatal_error(const char *message) {
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}

void manage_parent(int *pipe, int MAX_VALUE) {
    printf("Parent process (PID %d)\n", getpid());

    close(pipe[OUTPUT]);
    int i = 0;
    for( i = 0; i <= MAX_VALUE; i++) {
        write(pipe[INPUT], &i, sizeof(int));	
        printf("%d sent\n", i);
    }
    int end_signal = -1;
    write(pipe[INPUT], &end_signal, sizeof(int));
    close(pipe[INPUT]);	

    wait(NULL);	
    printf("Parent: has received child termination.\n");
}

void manage_child(int *pipe) {
    printf("Child process (PID %d)\n", getpid());	
    int received_value = 0;	
    close(pipe[INPUT]);	

    while (read(pipe[OUTPUT], &received_value, sizeof(int)) > 0) {	
        if (received_value == -1) {
            break;
        }
        printf("\n%d received\n", received_value);	
    }	

    close(pipe[OUTPUT]);	
    printf("Child process terminating.\n");
}

int main(int argc, char *argv[]) {
    clear_screen();

    pid_t pid;	    
    int anonymous_pipe[2];

    int MAX_VALUE = process_arguments(argc, argv);

    if (pipe(anonymous_pipe) == -1) {	
        handle_fatal_error("Error creating pipe.\n");	
    }

    switch (pid = fork()) {	
        case -1:	
            handle_fatal_error("Error using fork().\n");	
            break;	
        case 0:	
            manage_child(anonymous_pipe);	
            break;	
        default:	
            manage_parent(anonymous_pipe, MAX_VALUE);	
            break;	
    }

    return EXIT_SUCCESS;	
}

