#include "../include/sin_cos_g.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void plot_data(const char *filepath) {
    execlp("gnuplot", "gnuplot", "-persist", filepath, NULL);
    perror("Error executing gnuplot");
    exit(EXIT_FAILURE);
}
