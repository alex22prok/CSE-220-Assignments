#include "ceasar.h"

int encrypt(const char *plaintext, char *ciphertext, int key){
    // TO BE IMPLEMENTED   
    //null check
    if (!plaintext || !ciphertext)
    {
        return -2;
    }

    //insufficient memory space
    if((int)strlen(plaintext) + 8 > (int)strlen(ciphertext))
    {
        return -1;
    }


    //empty plaintext
    if (plaintext[0] == '\0') {
        const char *EOM = "__EOM__";
        int i = 0;
        for (; EOM[i] != '\0'; i++) {
            ciphertext[i] = EOM[i];
        }
        ciphertext[i] = '\0';
        return 0;
    }

    else
    {
        int i;
        int encrypted = 0;
        
        for (i = 0; plaintext[i] != '\0'; i++)
        {
            
            char current = plaintext[i];
            //if lowercase
            if (current >= 'a' && current <= 'z')
            {
                int shifted = (current - 'a' + key) % 26;
                if (shifted < 0) shifted += 26;
                ciphertext[i] = shifted + 'a';
                encrypted++;
            }
            //if UPPERCASE
            else if (current >= 'A' && current <= 'Z')
            {
                int shifted = (current - 'A' + key) % 26;
                if (shifted < 0) shifted += 26;
                ciphertext[i] = shifted + 'A';
                encrypted++;
            }
            //if #
            else if (current >= '0' && current <= '9')
            {
                int shifted = (current - '0' + key) % 10;
                if (shifted < 0) shifted += 10;
                ciphertext[i] = shifted + '0';
                encrypted++;
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
        return encrypted;
    }
    abort();
}

int decrypt(const char *ciphertext, char *plaintext, int key){
    // TO BE IMPLEMENTED
    if (!ciphertext || !plaintext)
    {
        return -2;
    }

    //empty buffer
    if (strlen(plaintext) == 0) 
    {   
        return 0;
    }
    
    //Find __EOM__ substring
    char *eom_ptr = strstr(ciphertext, "__EOM__");
    if (!eom_ptr)
    {
        return -1;
    }
    
    int eom_index = eom_ptr - ciphertext;
    if (eom_index == 0)
    {
        plaintext = "undefined\0";
        return 0;
    }
    else
    {
        int count = 0;
        int index = 0;
        for (int i = 0; i < eom_index; i++)
        {
            char current = ciphertext[i];
            //if lowercase
            if (current >= 'a' && current <= 'z')
            {
                plaintext[index++] = ((current - 'a' - key + 26) % 26) + 'a';
                count++;
            }
            //if UPPERCASE
            else if (current >= 'A' && current <= 'Z')
            {
                plaintext[index++] = ((current - 'A' - key + 26) % 26) + 'A';
                count++;
            }
            //if #
            else if (current >= '0' && current <= '9')
            {
                plaintext[index++] = ((current - '0' - key + 10) % 10) + '0';
                count++;
            }
            else
            {
                plaintext[index++] = current;
            }
            
        }
        //append null terminator
        plaintext[index] = '\0';
        return count;
    }
    abort();
}