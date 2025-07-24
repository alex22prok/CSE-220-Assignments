# CSE-220-Homework4
Name: Alexander Prokopiou
ID: 115449501

This is a program that encrypts/decrypts alphanumerical messages using the Ceasar Cipher Algorithm. You can skip over/ ignore non alphanumeric characters.

NOTE: All test cases are tested using Criterion. There is no main.c file. To test on your machine use:

    make 
    make test

# Guidelines:

1. The following content is a sample to follow. Describe the function in your own words. Design and describe your testcases under the student suite section.

2. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

3. The submitted code shouldn't produce any errors or warning messages.

4. Write brief comments in the source file to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

# Information about encrypt()/decrypt()

// Give short description about the function you implemented

## int encrypt(const char *plaintext, char *ciphertext, int key)

    Purpose: Encrypt a plaintext message using a ceaser cypher given the text, an output array, and encryption key

    Parameters: char array of plaintext input, char array for ouput encrypted message, and int encryption key

    Return Value: int: number of characters encoded, -1 for insufficient memory allocated for output, -2 if either char array is NULL 

    Further Notes: ciphertext is not treated as an array, but as a traditional string. It is always initialized of the size exactly as long as the string plus the null terminator. ciphertext is always long enough to store "undefined__EOM__" as is shown in the example test cases.

## int decrypt(const char *ciphertext, char *plaintext, int key) 

    Purpose: Decrypt a plaintext message using a ceaser cypher key given the encrypted message, an output array, and encryption key
     
    Parameters: char array of encrypted text input, char array for output of decrypted plaintext message, and int encryption key
    
    Return Value: int: number of decrypted characters, 0 if plaintext array length is 0, -1 if encrypted text is missing an EOM marker, and -2 if either char array is NULL

    Further Notes: ciphertext is not treated as an array, but as a traditional string. It is always initialized of the size exactly as long as the string plus the null terminator.

 ## Your Helper function (arguments,...)

    Purpose: N/A
  
    Parameters: N/A


## NOTES 

   Firstly, the idea that I should not worry about the memory allocated for ciphertext in encrypt() can't be good practice in C. It should either be stated explicitly that it is always to be initialized const char *ciphertext[] = "example", (ie. of the size of the string it is holding), or it should be of a reasonable size documented in the hw document (say 64 bytes).

   Secondly, the requirement which you relaxed about ciphertext being "undefined__EOM__" should have been explicitly stated alongside the return statements. I would have missed this requirement if I had not read piazza the morning 7/24. I should have all of the instructions written clearly such that I can complete the assignment when it comes out. 
      Furthermore, having to wait until recitation on Tuesday to see the expectation about criterion is ridiculous. I could have finished the homework before the recitation had you attached instruction to download criterion alongside documentation.

   Thirdly, by writing in the table of test cases under decryption: ciphertext --> empty__EOM__ , how am I supposed to interpret this? It's ambiguous, I can take a guess and assume it means "__EOM__"" but that is an assumption.

   
# Test Cases

## Student Suite

Includes various test cases to validate the `encrypt` and `decrypt` functions under different scenarios.

### Encrypt Tests

1. **Test Case: "xyz"**
   - **Plaintext**: "xyz"
   - **Ciphertext**: "abc__EOM__"
   - **Description**: Tests if lowercase letters wrap correctly from 'z' to 'a' using key `3`.

2. **Test Case: "789"**
   - **Plaintext**: "789"
   - **Ciphertext**: "123__EOM__"
   - **Description**: Tests if digits wrap correctly from '9' to '0' using key `4`.

3. **Test Case: "abc"**
   - **Plaintext**: "abc"
   - **Ciphertext**:"yza__EOM__"
   - **Description**: Tests if lowercase letters wrap correctly from 'a' to 'z' when using a negative key `-2`.

4. **Test Case: "XYZ"**
   - **Plaintext**: "XYZ"
   - **Ciphertext**:"ABC__EOM__"
   - **Description**: Tests if uppercase letters shift correctly and wrap from 'Z' to 'A' using key `3`.

5. **Test Case: Empty String**
   - **Plaintext**: ""
   - **Ciphertext**:"__EOM__"
   - **Description**: Tests behavior when encrypting an empty string. The result should only be the EOM marker, with a return value of `0`.

### Decrypt Tests

1. **Test Case: "HelloWorld123__EOM__"**
   - **Ciphertext**: "HelloWorld123__EOM__"
   - **Plaintext**: "HelloWorld123"
   - **Description**: Tests if characters remain unchanged when decrypting with key `0`.

2. **Test Case: "ABC012__EOM__"**
   - **Ciphertext**: "ABC012__EOM__"
   - **Plaintext**: "ZAB901"
   - **Description**: Tests if uppercase letters and digits wrap backward correctly using key `1`.

3. **Test Case: Empty Message "__EOM__"**
   - **Ciphertext**: "__EOM__"
   - **Plaintext**: ""
   - **Description**: Tests if decrypt returns `0` when valid ciphertext is empty.

4. **Test Case: No EOM "InvalidCiphertext"**
   - **Ciphertext**: "InvalidCiphertext"
   - **Plaintext**:  (unchanged)
   - **Description**: Tests if decrypt correctly returns `-1` when __EOM__ marker is missing from ciphertext.

5. **Test Case: "D1F__EOM__"**
   - **Ciphertext**: "D1F__EOM__"
   - **Plaintext**: "B9D"
   - **Description**: Tests if mixed uppercase letters and digits decrypt correctly with key `2`.

   
## Base Suite

Includes baseline tests provided by TAs to validate the `encrypt` and `decrypt` functions.

### Encrypt Tests

1. **Test Case: "System Fundamentals"**
   - **Plaintext**: "System Fundamentals"
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Description**: Tests if a full plaintext message can be encrypted with key `1`.

2. **Test Case: "Cse220"**
   - **Plaintext**: "Cse220"
   - **Ciphertext**: "Dtf331__EOM__"
   - **Description**: Tests if a full plaintext message with numbers can be encrypted with key `1`.

#### Decrypt Tests

1. **Test Case: "Tztufn Gvoebnfoubmt__EOM__"**
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Plaintext**: "System Fundamentals"
   - **Description**: Tests if a full ciphertext message can be decrypted with key `1`.

2. **Test Case: "Dtf331__EOM__"**
   - **Ciphertext**: "Dtf331__EOM__"
   - **Plaintext**: "Cse220"
   - **Description**: Tests if a full ciphertext message with numbers can be decrypted with key `1`.
