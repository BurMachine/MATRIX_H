#include "../s21_matrix.h"
#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

START_TEST(create_matrix) {
    int code = OK;
    matrix_t A = {0};
    code = s21_create_matrix(1, 1 , &A);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix1) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = 0;
            ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
        }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(mult_num) {
    const int rows = 2;
    const int cols = 2;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 1;
    m.matrix[1][0] = 1;
    m.matrix[1][1] = 1;
    check.matrix[0][0] = 2;
    check.matrix[0][1] = 2;
    check.matrix[1][0] = 2;
    check.matrix[1][1] = 2;
    int num = 2;
    matrix_t res = {0};
    s21_create_matrix(cols, rows, &res);
    ck_assert_int_eq(s21_mult_number(&m, num, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix) {
    const int rows = 2;
    const int cols = 2;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t check = {0};
    s21_create_matrix(cols, rows, &check);
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[1][0] = 3;
    m.matrix[1][1] = 4;
    check.matrix[0][0] = 1;
    check.matrix[0][1] = 3;
    check.matrix[1][0] = 2;
    check.matrix[1][1] = 4;
    matrix_t res = {0};
    s21_create_matrix(cols, rows, &res);
    ck_assert_int_eq(s21_transpose(&m, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_hardcode) {
    const int rows = 3;
    // const int rows = rand() % 100 + 1;
    const int cols = 3;
    // const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(cols, rows, &mtx);

    int md = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m.matrix[i][j] = md++;

    // m.matrix[i][j] = get_rand(-10e10, 10e10);
    int k1 = 1;
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            mtx.matrix[i][j] = k1++;
    // mtx.matrix[i][j] = get_rand(-10e10, 10e10);

    matrix_t check = {0};
    s21_create_matrix(m.rows, mtx.columns, &check);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < mtx.columns; j++) {
            check.matrix[i][j] = 0;
            for (int k = 0; k < m.columns; k++)
                check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
        }
    }

    matrix_t res = {0};
    s21_create_matrix(rows, rows, &res);

    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);


    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(complements_hardcoded) {
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    matrix_t expected = {0};
    s21_create_matrix(size, size, &expected);
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    matrix_t res = {0};
    s21_create_matrix(size, size, &res);
    s21_calc_complements(&m, &res);


    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(determinant_hardcoded) {
    const int rows = 3;
    const int cols = 3;
    matrix_t m1 = {0};

    s21_create_matrix(rows, cols, &m1);
    int m = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    m1.matrix[2][2] = 0;
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 27, 1e-6);
    ck_assert_int_eq(got, OK);
    s21_remove_matrix(&m1);
}
END_TEST START_TEST(determinant_no_zeros) {
    const int rows = 5;
    const int cols = 5;
    matrix_t m1 = {0};
    s21_create_matrix(rows, cols, &m1);
    int m = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 0, 1e-6);
    ck_assert_int_eq(got, OK);
    s21_remove_matrix(&m1);
}
END_TEST

// START_TEST(inverse_hardcoded) {
//     const int size = 3;
//     matrix_t m = {0};
//     s21_create_matrix(size, size, &m);
//     m.matrix[0][0] = 2;
//     m.matrix[0][1] = 5;
//     m.matrix[0][2] = 7;
//     m.matrix[1][0] = 6;
//     m.matrix[1][1] = 3;
//     m.matrix[1][2] = 4;
//     m.matrix[2][0] = 5;
//     m.matrix[2][1] = -2;
//     m.matrix[2][2] = -3;
//     matrix_t res = {0};
//     s21_create_matrix(size, size, &res);
//     s21_inverse_matrix(&m, &res);
//     matrix_t expected = {0};
//     s21_create_matrix(size, size, &expected);
//     expected.matrix[0][0] = 1;
//     expected.matrix[0][1] = -1;
//     expected.matrix[0][2] = 1;
//     expected.matrix[1][0] = -38;
//     expected.matrix[1][1] = 41;
//     expected.matrix[1][2] = -34;
//     expected.matrix[2][0] = 27;
//     expected.matrix[2][1] = -29;
//     expected.matrix[2][2] = 24;
//     ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
//     s21_remove_matrix(&expected);
//     s21_remove_matrix(&res);
//     s21_remove_matrix(&m);

// }
// END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int a;

    suite_add_tcase(s1, tc_1);
    tcase_add_test(tc_1, create_matrix);
    tcase_add_test(tc_1, create_matrix1);
    tcase_add_test(tc_1, transpose_matrix);
    tcase_add_test(tc_1, mult_hardcode);
    tcase_add_test(tc_1, complements_hardcoded);
    tcase_add_test(tc_1, determinant_hardcoded);
    tcase_add_test(tc_1, determinant_no_zeros);
    // tcase_add_test(tc_1, inverse_hardcoded);
    tcase_add_test(tc_1, mult_num);
    // tcase_add_test(tc_1, inverse_hardcoded);
    // tcase_add_test(tc_1, inverse_hardcoded);


    // tcase_add_loop_test(tc_1, create_matrix, 0, 100);
    // tcase_add_test(tc_1, no_rows);
    // tcase_add_test(tc_1, no_cols);
    // tcase_add_test(tc_1, not_eq);
    // tcase_add_loop_test(tc_1, eq_matrix, 0, 100);
    // tcase_add_loop_test(tc_1, sum_matrix, 0, 100);
    // tcase_add_loop_test(tc_1, sub_matrix, 0, 100);
    // tcase_add_loop_test(tc_1, mult_number, 0, 100);

    srunner_run_all(sr, CK_ENV);
    a = srunner_ntests_failed(sr);
    srunner_free(sr);

    return a == 0 ? 0 : 1;
}