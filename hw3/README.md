# CSE-220-Homework3
Name: {Alexander, Prokopiou}
ID: 115449501

# Bit Manipulation
Files: BitManipulation.c, BitManipulation (executable)

## Functions:
1. int main(int argc, char* argv[])
2. int GetBit(int num, int pos); // Return -1 on invalid input
3. int SetBit(int num, int pos); // Return -1 on invalid input
4. int ClearBit(int num, int pos); // Return -1 on invalid input
5. int Reversbit(int num);
6. int CountBit(int num);
7. int PowerofTwo(unsigned int num);

# Guidelines:

1. The folowing content is a sample to follow, please write your own test cases.

2. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

3. The submitted code shouldn't produce any errors or warning messages.

4. Write brief comments to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

## Test Cases:
1. int GetBit(int num, int pos);

	//Provided Test Cases
	//Testing regular number 12: 
	assert(GetBit(12, 0)==0); 

	//Testing 0 and -1 cases: 
	assert(GetBit(0, 0) == 0); 

	//Testing edge cases: 
	assert(GetBit(0xFFFFFFFF, 0) == 1);

	//Testing negative test cases: 
	assert(GetBit(-10, 0) == 0);   

	//Testing invalid positions: 
	assert(GetBit(10, 32)==-1);

	//My tests
		//1100 = bit 2 is 1
		assert(GetBit(12, 2) == 1);
		
		//All bits are 0
		assert(GetBit(0, 5) == 0);

		//Another invalid pos
		assert(GetBit(42, 32) == -1);


2. int SetBit(int num, int pos);

	//Test Cases
		//0000 → set bit 0 → 0001
		assert(SetBit(0, 0) == 1);

		//0100 → set bit 1 → 0110
		assert(SetBit(4, 1) == 6);

		//11110000 → set bit 0
		assert(SetBit(0xF0, 0) == 0xF1);

		//bit 4 already set       
		assert(SetBit(0xF0, 4) == 0xF0);
		
		//Invalid bit position
		assert(SetBit(100, 33) == -1);


3. int ClearBit(int num, int pos);

	//Test Cases
		//1111 → clear bit 0 → 1110
		assert(ClearBit(15, 0) == 14);

		//1111 → clear bit 3 → 0111
		assert(ClearBit(15, 3) == 7);

		//clear MSB
		assert(ClearBit(0xF0, 7) == 0x70);

		//bit already 0
		assert(ClearBit(0x00, 5) == 0x00);

		//Invalid bit position
		assert(ClearBit(50, 40) == -1);


4. int Reversbit(int num); // 

	//Test Cases
		//LSB becomes MSB
		assert((unsigned int)Reversbit(0x00000001) == 0x80000000);

		//00001111 → 11110000...
		assert((unsigned int)Reversbit(0x0000000F) == 0xF0000000);

		//All 1s
		assert((unsigned int)Reversbit(0xFFFFFFFF) == 0xFFFFFFFF);

		//pattern symmetry
		assert((unsigned int)Reversbit(0x0F0F0F0F) == 0xF0F0F0F0);

		//All 0s stay 0
		assert((unsigned int)Reversbit(0x00000000) == 0x00000000);


5. int CountBit(int num);

	//Test Cases 
		//No 1s
		assert(CountBit(0) == 0);

		//Only LSB is 1
		assert(CountBit(1) == 1);

		//All bits are 1
		assert(CountBit(0xFFFFFFFF) == 32);

		//Alternating 4-bit groups
		assert(CountBit(0xF0F0F0F0) == 16);

		//Only MSB is 1
		assert(CountBit(0x80000000) == 1);


6. int PowerofTwo(unsigned int num);

	//Test Cases
		//Not a power of two
		assert(PowerofTwo(0) == 0);

		//2^0 = 1
		assert(PowerofTwo(1) == 1);

		//2^1 = 2
		assert(PowerofTwo(2) == 1);

		//Not a power of two
		assert(PowerofTwo(3) == 0);

		//2^10 = 1024
		assert(PowerofTwo(1024) == 1);


# IEEE 754 Float 
Files: float.c, float (executable)

## Functions:
1. int main(int argc, char* argv[])
2. float construct_float_sf(char sign_bit, char exponent, unsigned int fraction)

## Note
{
	//unsure whether in MakeFile clean is supposed to say aloat or float
	//Compiler warnings about implicit conversion from 'float' to 'double' were ignored as per instructions
		//float runs regardless
}

## Test Cases: 
{
    //Normal Test Cases:
    printf("f = %g\n", construct_float_sf(arg1,arg2,arg3));

    //Special/Edge Cases:
    printf("f = %g\n", construct_float_sf(arg1,arg2,arg3));

	//Provided Test Cases in HW Document
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
    printf("f = %g\n", construct_float_sf(0x01, 0x86, 0x480000)); //-100.75 check

    //Very large number
    printf("f = %e\n", construct_float_sf(0x00, 0xFE, 0x000000)); //1.70141e+38 or 1.0 × 2^127

    //-pi
    printf("f = %g\n", construct_float_sf(0x01, 0x80, 0x492492)); //-3.14159

    //Random idk
    printf("f = %g\n", construct_float_sf(0x00, 0x7F, 0x173B2A)); //1522474 check
}

