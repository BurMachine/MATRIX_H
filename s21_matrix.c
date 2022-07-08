#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int code = 0;

    if (rows > 0 && columns > 0) {
        result->columns = columns;
        result->rows = rows;

    }
