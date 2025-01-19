#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/sin_cos.h"
#include "../include/sin_cos_g.h"

#define MAX_ANGLE 360
#define STEP 10

pid_t child1_pid, child2_pid;
volatile sig_atomic_t angle = 0; 

void child1_handler(int signum) {
    double value = calcul_cos_sin(1, (float)angle);
    print_data(1, 1, getpid(), value, (float)angle);

    angle += STEP;
    if (angle > MAX_ANGLE) {
        kill(getppid(), SIGUSR1);
        exit(0);
    }
}

void child2_handler(int signum) {
    double value = calcul_cos_sin(2, (float)angle);
    print_data(2, 2, getpid(), value, (float)angle);

    angle += STEP;
    if (angle > MAX_ANGLE) {
        kill(getppid(), SIGUSR1);
        exit(0);
    }
}

void alarm_handler(int signum) {
    static int active_child = 1;

    if (angle > MAX_ANGLE) {
        return; 
    }

    if (active_child == 1) {
        kill(child1_pid, SIGUSR1);
        active_child = 2;
    } else {
        kill(child2_pid, SIGUSR1);
        active_child = 1;
    }

    alarm(1);
}

void restart_processes() {
    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    printf("Restarting with new processes for plotting...\n");

    if ((child1_pid = fork()) == 0) {
        printf("Graphic for cosinus by PID %d.\n", getpid());
        plot_data("./commande_cos.gp");
    }

    if ((child2_pid = fork()) == 0) {
        printf("Graphic for sinus by PID %d.\n", getpid());
        plot_data("./commande_sin.gp");
    }

    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    printf("Plotting completed. Program terminated.\n");
    exit(0);
}

void termination_handler(int signum) {
    restart_processes();
}

int main() {
    struct sigaction sa_alarm, sa_child1, sa_child2, sa_termination;

    sa_alarm.sa_handler = alarm_handler;
    sigemptyset(&sa_alarm.sa_mask);
    sa_alarm.sa_flags = 0;
    sigaction(SIGALRM, &sa_alarm, NULL);

    sa_termination.sa_handler = termination_handler;
    sigemptyset(&sa_termination.sa_mask);
    sa_termination.sa_flags = 0;
    sigaction(SIGUSR1, &sa_termination, NULL);

    if ((child1_pid = fork()) == 0) {
        sa_child1.sa_handler = child1_handler;
        sigemptyset(&sa_child1.sa_mask);
        sa_child1.sa_flags = 0;
        sigaction(SIGUSR1, &sa_child1, NULL);

        while (1) pause();
    }

    if ((child2_pid = fork()) == 0) {
        sa_child2.sa_handler = child2_handler;
        sigemptyset(&sa_child2.sa_mask);
        sa_child2.sa_flags = 0;
        sigaction(SIGUSR1, &sa_child2, NULL);

        while (1) pause();
    }

    angle = 0;
    alarm(1);

    while (1) pause();
    return 0;
}