#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    pid_t pid;

    if ((pid = fork()) == 0) {
        printf("Child 1: Executing Firefox with two tabs\n");
        char *args[] = {"firefox", "--new-window", "https://foad.ensicaen.fr", "https://gitlab.ecole.ensicaen.fr", NULL};
        execvp("firefox", args);
        perror("Error executing Firefox");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == 0) {
        printf("Child 2: Executing Firefox with search query\n");
        char *args[] = {"firefox", "--search", "Codeium Vim", NULL};
        execvp("firefox", args);
        perror("Error executing Firefox");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == 0) {
        printf("Child 3: Executing gedit with file %s\n", filename);
        char *args[] = {"gedit", filename, NULL};
        execvp("gedit", args);
        perror("Error executing gedit");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == 0) {
        printf("Child 4: Executing evince with file %s\n", filename);
        char *args[] = {"evince", filename, NULL};
        execvp("evince", args);
        perror("Error executing evince");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    printf("All child processes have finished.\n");
    return 0;
}
