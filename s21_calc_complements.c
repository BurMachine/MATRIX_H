//
// Created by User on 011 11.07.22.
//
#include "s21_matrix.h"
#include "stdio.h"

static void less_dim(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int code = OK;

    if (!A || A->rows < 1 || A->columns < 1) {
        code = INCORRECT_MATRIX;
    } else if(A->rows != A->columns) {
        code = CALC_ERROR;
    } else {
        code = s21_create_matrix(A->rows, A->columns, result);
    }

    if (code == OK) less_dim(A, result);
    return code;
}


void get_minor_matrix(double **m, double **tmp, int skip_row, int skip_col, int size) {
    for (int row = 0, i = 0, j = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row != skip_row && col != skip_col) {
                tmp[i][j] = m[row][col];
                j++;
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

static void less_dim(matrix_t *A, matrix_t *result) {
    if (A->rows == 1) {
        result->matrix[0][0] = 1;
        return;
    }
    int size = A->rows;
    double **tmp = malloc(sizeof(double *) * size);
    if (!tmp)
        error();
    for (int i = 0; i < size; i++) {
        tmp[i] = malloc(sizeof(double) * size);
        if (!tmp[i])
            error();
    }
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            get_minor_matrix(A->matrix, tmp, i, j, size);
            result->matrix[i][j] = sign * determinant_rec(tmp, size - 1);
            sign = -sign;
        }
    }
    for (int i = 0; i < size; i++)
        free(tmp[i]);
    free(tmp);
}



noreturn void error(void) {
    fprintf(stderr, "Malloc error\n");
    errno = ENOMEM;
    perror("Memory error");
    exit(0);
}