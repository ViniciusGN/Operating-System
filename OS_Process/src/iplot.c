#include "../include/iplot.h"
#include <stdio.h>
#include <stdlib.h>

int create_file(char *value, int interval_type, const char *filepath) {
    FILE *pont_file;

    pont_file = fopen(filepath, "w");

    if (pont_file == NULL) {
        printf("Error: creating file %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    fprintf(pont_file, "set samples 500\n");
    fprintf(pont_file, "set title \"Sinus cardinal\"\n");
    fprintf(pont_file, "set xlabel \"x\"\n");
    fprintf(pont_file, "set ylabel \"sin(x)/x\"\n");

    if (interval_type == 1) {
        fprintf(pont_file, "set xrange [-%s:%s]\n", value, value);
    } else {
        fprintf(pont_file, "set xrange [0:%s]\n", value);
    }

    fprintf(pont_file, "set border\n");
    fprintf(pont_file, "set grid\n");
    fprintf(pont_file, "plot sin(x)/x\n");

    fclose(pont_file);
    return 1;
}

void plot_data(const char *filepath) {
    execlp("gnuplot", "gnuplot", "-persist", filepath, NULL);
    perror("Error executing gnuplot");
    exit(EXIT_FAILURE);
}
