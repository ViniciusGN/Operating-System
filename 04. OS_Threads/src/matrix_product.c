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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <matrix.h>

/* Mono thread functions */
void mono_thread(matrix_t *m1, matrix_t *m2) 
{
	matrix_t *m3;
	clock_t c_before;
	clock_t c_after;
	time_t t_before;
	time_t t_after;

	c_before = clock();
	t_before = time(NULL);
	m3 = product_matrix(m1, m2);
	t_after = time(NULL);
	c_after = clock();

	if (PRINT) {
		printf("\nProduct :\n");
		print_matrix(m3);
	}

	printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
			 (float) (c_after - c_before),
			 (double) (c_after - c_before) / CLOCKS_PER_SEC);
	printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

	free_matrix(m3->matrix);
	free(m3);
}



matrix_t *product_matrix(matrix_t *m1, matrix_t *m2) 
{
	unsigned int i;
	unsigned int j;
	matrix_t *result;

	if (m1->columns != m2->rows) {
		printf("Dimensions Error\n");
		return NULL;
	}

	result = init_matrix(m1->rows, m2->columns, 0);

	for (i = 0; i < result->columns; ++i) {
		for (j = 0; j < result->rows; ++j) {
			result->matrix[j][i] = product_case(j, i, m1, m2);
		}
	}

	return result;
}

/*  MY CODE HERE */

void *product_matrix_thread(void *args) {
    args_t *data = (args_t *)args;
    int start = data->start_row;
    int end = data->end_row;
    matrix_t *m1 = data->m1;
    matrix_t *m2 = data->m2;
    matrix_t *answer = data->answer;

    int i, j, k;
    for (i = start; i < end; i++) {
        for (j = 0; j < (int)m2->columns; j++) {
            answer->matrix[i][j] = 0;
            for (k = 0; k < (int)m1->columns; k++) {
                answer->matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
            }
        }
    }

    return NULL;
}

void multi_thread(matrix_t *m1, matrix_t *m2, int num_threads) {
    if (m1->columns != m2->rows) {
        printf("Dimensions Error\n");
        return;
    }

    matrix_t *answer = init_matrix(m1->rows, m2->columns, 0);
    pthread_t *threads_id = malloc(num_threads * sizeof(pthread_t));
    args_t *args = malloc(num_threads * sizeof(args_t));

    int rows_per_thread = m1->rows / num_threads;
    int remaining_rows = m1->rows % num_threads;

    clock_t c_before = clock();
    time_t t_before = time(NULL);

    int i;
    for (i = 0; i < num_threads; i++) {
        args[i].m1 = m1;
        args[i].m2 = m2;
        args[i].answer = answer;
        args[i].start_row = i * rows_per_thread;
        args[i].end_row = (i + 1) * rows_per_thread;

        if (i == num_threads - 1) {
            args[i].end_row += remaining_rows;
        }

        pthread_create(&threads_id[i], NULL, product_matrix_thread, &args[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads_id[i], NULL);
    }

    clock_t c_after = clock();
    time_t t_after = time(NULL);

    if (PRINT) {
        printf("\nProduct :\n");
        print_matrix(answer);
    }

    printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
           (float)(c_after - c_before),
           (double)(c_after - c_before) / CLOCKS_PER_SEC);
    printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

    free_matrix(answer->matrix);
    free(answer);
    free(threads_id);
    free(args);
}

/* ------------------------------------- */

double product_case(int r, int c, matrix_t *m1, matrix_t *m2) 
{
	unsigned int i;
	double tmp;
	
	tmp = 0;

	for (i = 0; i < m1->columns; ++i) {
		tmp += m1->matrix[r][i] * m2->matrix[i][c];
	}

	return tmp;
}

/* Utils matrix functions */

void print_matrix(matrix_t *m) 
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < m->rows; ++i) {
		for (j = 0; j < m->columns; ++j) {
			printf("%04.2f ", m->matrix[i][j]);
		}
		printf("\n");
	}
}

matrix_t *init_matrix(unsigned int rows, unsigned int columns, int fill) 
{
	matrix_t *m;
	
	m = malloc(sizeof(matrix_t));
	m->rows = rows;
	m->columns = columns;
	m->matrix = alloc_matrix(rows, columns);

	if (fill) {
		fill_matrix(m);
	}

	return m;
}

void fill_matrix(matrix_t *m) 
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < m->rows; ++i) {
		for (j = 0; j < m->columns; ++j) {
			m->matrix[i][j] = (double) (rand() % 15) + 10;
		}
	}
}

double **alloc_matrix(unsigned int rows, unsigned int columns) 
{
	double **matrix;
	unsigned int row;

	matrix = (double **) calloc(rows, sizeof(double *));
	if (!matrix) {
		return NULL;
	}

	matrix[0] = (double *) calloc(rows * columns, sizeof(double));
	if (!matrix[0]) {
		free(matrix);
		return NULL;
	}

	for (row = 1; row < rows; ++row) {
		matrix[row] = matrix[row - 1] + columns;
	}

	return matrix;
}

void free_matrix(double **matrix) 
{
	free(matrix[0]);
	free(matrix);
}
