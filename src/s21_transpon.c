//
// Created by User on 008 08.07.22.
//
#include "s21_matrix.h"


int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = s21_create_matrix(A->rows, A->columns, result);
  if (code == OK) {
      for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
              result->matrix[j][i] = A->matrix[i][j];
          }
      }
  }
  return code;
}