#include <stdio.h>
#include <stdint.h>

float construct_float_sf(char sign_bit, char exponent, unsigned int fraction) {
    /* DO NOT CHANGE THE DECLARATION OF "f" (This will be converted to float later) */
    unsigned int f = 0; // DO NOT CHANGE
    /*------------------------------------------------------------------------------*/
    
    /* Start Coding Here */
    
    //Set sign bit on MSB
    f |= (((unsigned int)sign_bit & 0x1) << 31);
    //Set exponent bits at appropriate location 
    f |= (((unsigned int)exponent & 0xFF) << 23);
    //set fraction bits
    f |= ((fraction & 0x7FFFFF));
    /*-------------------*/
    
    /* DO NOT CHANGE THE RETURN VALUE (This returns the binary representation of "f" as float) */
    return *((float*)&f); // DO NOT CHANGE
    /* ----------------------------------------------------------------------------------------*/
}

#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[])
{
    (void) argc; // to supress compiler warning
    (void)argv;  // to supress compiler warning     
    printf("f = %g\n", construct_float_sf(0x00, 0x00, 0x000000));
    
    //provided test cases
    printf("f = %g\n", construct_float_sf(0x00, 0x81, 0x300000)); //5.5
    printf("f = %g\n", construct_float_sf(0x01, 0x81, 0x300000)); //-5.5
    printf("f = %g\n", construct_float_sf(0x00, 0x7F, 0x200000)); //1.25
    printf("f = %g\n", construct_float_sf(0x01, 0x7F, 0x200000)); //-1.25
    printf("f = %g\n", construct_float_sf(0x00, 0x76, 0x299B6F)); //0.002588
    printf("f = %g\n", construct_float_sf(0x01, 0x76, 0x299B6F)); //-0.002588
    printf("f = %g\n", construct_float_sf(0x00, 0x89, 0xABCDEF)); //1374.44
    printf("f = %g\n", construct_float_sf(0x01, 0x89, 0xABCDEF)); //-1374.44
    printf("f = %g\n", construct_float_sf(0x00, 0x90, 0x7973C0)); //255439

    //New testcases

    //negative 0
    printf("f = %g\n", construct_float_sf(0x01, 0x00, 0x000000)); //-0

    //Tiny number
    printf("f = %e\n", construct_float_sf(0x00, 0x01, 0x000000)); //1.17549e-38 = 2^-126

    //A half
    printf("f = %g\n", construct_float_sf(0x00, 0x7E, 0x000000)); //0.5

    //2
    printf("f = %g\n", construct_float_sf(0x00, 0x80, 0x000000)); //2

    //-100.75
    printf("f = %g\n", construct_float_sf(0x01, 0x85, 0x498000)); //-100.75

    //Very large number
    printf("f = %e\n", construct_float_sf(0x00, 0xFE, 0x000000)); //1.70141e+38 or 1.0 × 2^127

    //-pi
    printf("f = %g\n", construct_float_sf(0x01, 0x80, 0x492492)); //-3.14159

    //Random idk
    printf("f = %g\n", construct_float_sf(0x00, 0x93, 0x39D950)); //1522474
    return 0;
}
#endif /* Do not remove this line*/

