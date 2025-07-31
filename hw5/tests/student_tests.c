#include "global.h"
#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/


//SparseMatrix
Test(student_suite, sparse_all_zeros, .description="SparseMatrix: All elements are 0") {
    int** M = initializeMatrix(2, 3, (int[]){0, 0, 0, 0, 0, 0});
    int** S = initializeMatrix(1, 4, (int[]){0, 0, 0, 0});
    int ret = SparseMatrix(2, 3, M, S);
    cr_assert_eq(ret, 0, "Should return 0 for all-zero matrix");
    freeMatrix(2, M);
    freeMatrix(1, S);
}

Test(student_suite, sparse_exact_threshold, .description="SparseMatrix: Density exactly at threshold") {
    //Max(row, col) = 3; max non-zero allowed = 3
    int** M = initializeMatrix(2, 3, (int[]){0, 1, 0, 2, 0, 3});
    int** S = initializeMatrix(3, 4, (int[]){0});
    int ret = SparseMatrix(2, 3, M, S);
    cr_assert_eq(ret, 3, "Should return 3 when density is at threshold");
    freeMatrix(2, M);
    freeMatrix(3, S);
}

Test(student_suite, sparse_too_dense, .description="SparseMatrix: Matrix too dense") {
    int** M = initializeMatrix(2, 2, (int[]){1, 1, 1, 1});
    int** S = initializeMatrix(4, 4, (int[]){0});
    int ret = SparseMatrix(2, 2, M, S);
    cr_assert_eq(ret, -1, "Should return -1 for too dense matrix");
    freeMatrix(2, M);
    freeMatrix(4, S);
}


//Addition
Test(student_suite, addition_negative_values, .description="Addition: Matrices contain negative values") {
    int** M = initializeMatrix(2, 2, (int[]){5, -3, 2, -1});
    int** N = initializeMatrix(2, 2, (int[]){-5, 3, -2, 1});
    int** A = initializeMatrix(2, 2, (int[]){0});
    int** expected = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int ret = Addition(2, 2, 2, 2, 2, 2, M, N, A);
    cr_assert_eq(ret, 1, "Expected return value 1 for compatible addition");
    cr_assert(areMatricesEqual(A, expected, 2, 2), "Expected result matrix of all zeroes");
    freeMatrix(2, M); freeMatrix(2, N); freeMatrix(2, A); freeMatrix(2, expected);
}


//Multiplication
Test(student_suite, multiplication_with_identity, .description="Multiplication: M * I = M") {
    int** M = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** I = initializeMatrix(2, 2, (int[]){1, 0, 0, 1});
    int** A = initializeMatrix(2, 2, (int[]){0});
    int** expected = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int ret = Multiplication(2, 2, 2, 2, 2, 2, M, I, A);
    cr_assert_eq(ret, 1);
    cr_assert(areMatricesEqual(A, expected, 2, 2));
    freeMatrix(2, M); freeMatrix(2, I); freeMatrix(2, A); freeMatrix(2, expected);
}

Test(student_suite, multiplication_with_zeros, .description="Multiplication: M * 0 = 0") {
    int** M = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** Z = initializeMatrix(3, 2, (int[]){0});
    int** A = initializeMatrix(2, 2, (int[]){-1, -1, -1, -1});
    int** expected = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int ret = Multiplication(2, 3, 3, 2, 2, 2, M, Z, A);
    cr_assert_eq(ret, 1);
    cr_assert(areMatricesEqual(A, expected, 2, 2));
    freeMatrix(2, M); freeMatrix(3, Z); freeMatrix(2, A); freeMatrix(2, expected);
}


//Transpose
Test(student_suite, transpose_1x1, .description="Transpose: 1x1 matrix") {
    int** M = initializeMatrix(1, 1, (int[]){42});
    int** AT = initializeMatrix(1, 1, (int[]){0});
    int** expected = initializeMatrix(1, 1, (int[]){42});
    int ret = Transpose(1, 1, 1, 1, M, AT);
    cr_assert_eq(ret, 1);
    cr_assert(areMatricesEqual(AT, expected, 1, 1));
    freeMatrix(1, M); freeMatrix(1, AT); freeMatrix(1, expected);
}

Test(student_suite, transpose_1xN, .description="Transpose: 1xN matrix becomes Nx1") {
    int** M = initializeMatrix(1, 3, (int[]){1, 2, 3});
    int** AT = initializeMatrix(3, 1, (int[]){0, 0, 0});
    int** expected = initializeMatrix(3, 1, (int[]){1, 2, 3});
    int ret = Transpose(1, 3, 3, 1, M, AT);
    cr_assert_eq(ret, 1);
    cr_assert(areMatricesEqual(AT, expected, 3, 1));
    freeMatrix(1, M); freeMatrix(3, AT); freeMatrix(3, expected);
}


