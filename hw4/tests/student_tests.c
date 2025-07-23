#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/

//ENCRYPT
//lowercase wraparound
Test(base_suite, encrypt_lowercase_wraparound, .description="Lowercase letters wrapping from z to a") {
    const char *plaintext = "xyz";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 3);
    char *ciphertext_exp = "abc__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//digit wraparound
Test(base_suite, encrypt_digit_wraparound, .description="Digits wrapping from 9 to 0") {
    const char *plaintext = "789";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 4);
    char *ciphertext_exp = "123__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//DECRYPT
//key = 0
Test(base_suite, decrypt_no_shift, .description="Key = 0 should not change any character") {
    const char *ciphertext = "HelloWorld123__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 0);
    char *plaintext_exp = "HelloWorld123";
    int count_exp = 13;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//Uppercase and digit wraparound
Test(base_suite, decrypt_uppercase_digit_wrap, .description="Uppercase and digits wrapping backwards") {
    const char *ciphertext = "ABC012__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "ZAB901";
    int count_exp = 6;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}