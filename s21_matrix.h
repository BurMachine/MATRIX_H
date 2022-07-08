#ifndef _S21_MATRIX_
#define _S21_MATRIX_

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
#define MALLOC_ERROR 3

#define FAIL 0
#define SUCCESS 1

#define EPS 1e-8

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

void printner(matrix_t matrix);
int check_for_add_sub(matrix_t a, matrix_t b);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);



#endif // _S21_MATRIX_
