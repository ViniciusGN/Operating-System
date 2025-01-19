#include "../include/sin_cos.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calcul_cos_sin(int type, float angle) {
    double radians = angle * (M_PI / 180.0);
    if (type == 1) {
        return sin(radians);
    } else if (type == 2) {
        return cos(radians);
    } else {
        fprintf(stderr, "Invalid type for calculation: %d\n", type);
        exit(EXIT_FAILURE);
    }
}

void print_data(int type, int child_number, int pid_child, double value, float angle) {
    if (type == 1) {
        printf("Fils %d (%d): sinus(%f) = %f\n", child_number, pid_child, angle, value);
        register_data(type, angle, value, "./sinus.txt");
    } else if (type == 2) {
        printf("Fils %d (%d): cosinus(%f) = %f\n", child_number, pid_child, angle, value);
        register_data(type, angle, value, "./cosinus.txt");
    }
}

void register_data(int type, float angle, double value, const char *filepath) {
    FILE *pont_file = fopen(filepath, "a");
    if (pont_file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(pont_file, "%f %f\n", angle, value);
    fclose(pont_file);
}