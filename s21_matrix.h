#ifndef _S21_MATRIX_
#define _S21_MATRIX_

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
#define MALLOC_ERROR 3

#define FAIL 0
#define SUCCESS 1


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

void printner(matrix_t matrix);

int s21_create_matrix(int rows, int columns, matrix_t *result);


#endif // _S21_MATRIX_
