#include "ceasar.h"

int encrypt(const char *plaintext, char *ciphertext, int key){
    // TO BE IMPLEMENTED
    int output_buffer = 31;
    //null check
    if (!plaintext || !ciphertext)
    {
        return -2;
    }

    //insufficient memory space
    if((int)strlen(plaintext) + 8 > output_buffer)
    {
        return -1;
    }

    int i;
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        
        char current = plaintext[i];
        //if lowercase
        if (current >= 'a' && current <= 'z')
        {
            ciphertext[i] = ((current - 'a' + key) % 26) + 'a';
        }
        //if UPPERCASE
        if (current >= 'A' && current <= 'Z')
        {
            ciphertext[i] = ((current - 'A' + key) % 26) + 'A';
        }
        //if #
        if (current >= '0' && current <= '9')
        {
            ciphertext[i] = ((current - '0' + key) % 10) + '0';
        }
        else
        {
            ciphertext[i] = current;
        }
    }

    //Append "__EOM__"
    const char *EOM = "__EOM__";
    for (int j = 0; EOM[j] != '\0'; j++)
    {
        ciphertext[i++] = EOM[j];
    }

    //terminate string
    ciphertext[i] = '\0';
    
    //return # of chars excluding EOM
    return i-7;

    abort();
}

int decrypt(const char *ciphertext, char *plaintext, int key){
    // TO BE IMPLEMENTED
    if (!ciphertext || !plaintext)
    {
        return -2;
    }

    if (strlen(plaintext) == 0) return 0;

    //Find __EOM__ substring
    char *eom = strstr(ciphertext, "__EOM__");
    if (!eom)
    {
        return -1;
    }

    int count = 0;
     for (int i = 0; &ciphertext[i] < eom; i++)
    {
        char current = ciphertext[i];
        //if lowercase
        if (current >= 'a' && current <= 'z')
        {
            plaintext[count++] = ((current - 'a' - key + 26) % 26) + 'a';
        }
        //if UPPERCASE
        if (current >= 'A' && current <= 'Z')
        {
            plaintext[count++] = ((current - 'A' - key + 26) % 26) + 'A';
        }
        //if #
        if (current >= '0' && current <= '9')
        {
            plaintext[count++] = ((current - '0' - key + 10) % 10) + '0';
        }
        else
        {
            plaintext[count++] = current;
        }
    }

    plaintext[count] = '\0';
    return count;
    abort();
}