// The default behavior is to not pass the optional parameter, in which case the interval is [0, B].
// If the user provides the "-i" parameter, the interval is changed to [-B, B].
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/iplot.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <B> [-i]\n", argv[0]);
        return 1;
    }

    char *B = argv[1];
    int interval_type = 0;
    char *filepath = "commandes.gp";

    if (argc == 3 && strcmp(argv[2], "-i") == 0) {
        interval_type = 1;
    }

    pid_t childPid;

    if (create_file(B, interval_type, filepath) == 1) {
        printf("File commandes.gp is created in folder 'file'!\n");
    }

    switch (childPid = fork()) {
        case -1:
            perror("Error forking process");
            exit(EXIT_FAILURE);
        case 0:
            printf("In child process, PID: %d\n", getpid());
            plot_data(filepath);
            break;
        default:
            printf("In parent process, PID: %d\n", getpid());
            break;
    }

    return 0;
}

