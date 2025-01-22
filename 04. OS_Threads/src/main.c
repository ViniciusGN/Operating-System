/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * Unix System Programming
 * Chapter "Threads"
 *
 * 2016 Alain Lebret (alain.lebret@ensicaen.fr)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matrix.h>

void test_raport();

int main(int argc, char *argv[]) 
{
	matrix_t *m1;
    matrix_t *m2;
    int num_threads = THREAD_DEFAULT;
    int size = SIZE;
    int execute_test = 0;

	for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) { 
            if (i + 1 < argc) {
                num_threads = atoi(argv[++i]);
                if (num_threads < 1 || num_threads > THREAD_MAX) {
                    printf("Invalid number of threads! Using default (%d).\n", THREAD_DEFAULT);
                    num_threads = THREAD_DEFAULT;
                }
            } else {
                printf("Incorrect use of -t. Using the default (%d).\n", THREAD_DEFAULT);
                num_threads = THREAD_DEFAULT;
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                size = atoi(argv[++i]);
                if (size < 10 || size > 10000) {
                    printf("Invalid array size! Using default(%d).\n", SIZE);
                    size = SIZE;
                }
            } else {
                printf("Incorrect use of -s. Using the default (%d).\n", SIZE);
                size = SIZE;
            }
        } else if (strcmp(argv[i], "-E") == 0) {
            execute_test = 1;
        }
    }

    if (execute_test && argc == 2) {
        printf("Running Report Tests...\n");
        test_raport();
        exit(EXIT_SUCCESS);
    }

	printf("Using %d thread(s).\n", num_threads);

	m1 = init_matrix(SIZE, SIZE, 1);
	m2 = init_matrix(SIZE, SIZE, 1);

	if (PRINT) {
		printf("Matrix m1\n");
		print_matrix(m1);
		printf("\nMatrix m2\n");
		print_matrix(m2);
	}

	printf("\n======== Mono   Thread ========\n");
	mono_thread(m1, m2);

	printf("\n======== Multi Threads ========\n\n");
	multi_thread(m1, m2, num_threads);

	free_matrix(m1->matrix);
	free_matrix(m2->matrix);

	free(m1);
	free(m2);

	exit(EXIT_SUCCESS);
}

void test_raport() {
    int sizes[] = {10, 100, 500, 1000, 2000, 3000, 5000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int threads[] = {12};
    int num_threads = sizeof(threads) / sizeof(threads[0]);

    for (int t = 0; t < num_threads; t++) {
        for (int s = 0; s < num_sizes; s++) {
            printf("\n=== Testing matrix %dx%d with %d thread(s) ===\n", sizes[s], sizes[s], threads[t]);
            matrix_t *m1 = init_matrix(sizes[s], sizes[s], 1);
            matrix_t *m2 = init_matrix(sizes[s], sizes[s], 1);

            printf("\nMono Thread:\n");
            mono_thread(m1, m2);

            printf("\nMulti Thread:\n");
            multi_thread(m1, m2, threads[t]);

            free_matrix(m1->matrix);
            free_matrix(m2->matrix);
            free(m1);
            free(m2);
        }
    }
}
