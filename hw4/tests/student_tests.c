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

//negative key
Test(base_suite, encrypt_negative_key_wrap, .description="Lowercase letters wrapping from a to z with negative key") {
    const char *plaintext = "abc";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, -2);
    char *ciphertext_exp = "yza__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//UPPERCASE wraparound
Test(base_suite, encrypt_uppercase_shift, .description="Uppercase letters shift correctly with positive key") {
    const char *plaintext = "XYZ";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 3);
    char *ciphertext_exp = "ABC__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//empty string
Test(base_suite, encrypt_empty_string, .description="Plaintext is an empty string") {
    const char *plaintext = "";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 5);
    char *ciphertext_exp = "__EOM__";
    int count_exp = 0;
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

//Decrypt empty
Test(base_suite, decrypt_empty_buffer, .description= "ciphertext buffer contains no message, decryption should return 0") {
    const char *ciphertext = "__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    int count_exp = 0;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//Missing EOM
Test(base_suite, decrypt_missing_eom, .description="Ciphertext is missing the __EOM__ marker") {
    const char *ciphertext = "InvalidCiphertext";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    int count_exp = -1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d (missing EOM).\n", count_act, count_exp);
}

//Mixed Characters
Test(base_suite, decrypt_mixed_alphanumeric, .description="Mixed letters and digits decrypt correctly") {
    const char *ciphertext = "D1F__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    char *plaintext_exp = "B9D";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}
