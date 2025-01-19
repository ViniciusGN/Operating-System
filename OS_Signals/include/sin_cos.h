#ifndef SIN_COS_H
#define SIN_COS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

double calcul_cos_sin(int type, float angle);
void print_data(int type, int child_number, int pid_child, double value, float angle);
void register_data(int type, float angle, double value, const char *filepath);

#endif // SIN_COS_H
