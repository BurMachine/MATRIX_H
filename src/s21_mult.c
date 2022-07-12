//
// Created by User on 008 08.07.22.
//
#include "s21_matrix.h"


int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int code = s21_create_matrix(A->rows, A->columns, result);
    if (code == OK) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = number * A->matrix[i][j];
            }
        }
    }
    return code;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = OK;
    // if (check_for_add_sub(*A, *B) != OK) code = INCORRECT_MATRIX;

    if (A->columns != B->rows) code = CALC_ERROR;

    code = s21_create_matrix(A->rows, B->columns, result);

    if (code == OK) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                result->matrix[i][j] = 0;
                for (int k = 0; k < B->rows; k++) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return code;
}
