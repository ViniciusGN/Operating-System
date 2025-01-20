#ifndef FSIEVE_H
#define FSIEVE_H
#include <stdio.h>
#include <stdlib.h>

void manage_parent(int pipes[2], int MAX_VALUE);
void manage_childs(int received_pipes[2], int piper_number, int responsability);
void save_primes(int prime);
void handle_fatal_error(const char *message);

#endif
