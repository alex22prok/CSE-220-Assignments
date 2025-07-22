#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int GetBit(int num, int pos);
int SetBit(int num, int pos);
int ClearBit(int num, int pos);
int Reversbit(int num);
int CountBit(int num);
int PowerofTwo(unsigned int num);



#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[]){
	(void)argc;
	(void)argv;


	//GetBit

	//Provided Tests
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

	//SetBit
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
	
	//ClearBit
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

	//Reversbit
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

	//CountBit
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
		
	//PowerofTwo
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
	
	return 0;
}
#endif /* Do not remove this line*/

//Get the Bit in desired position
int GetBit(int num, int pos)
{
	//Check valid position
	if (pos < 0 || pos > 31) return -1;
	//Shift desired position to LSB and mask with 1 (000...001)
	return (num >> pos) & 1;
}

//Sets Bit in desired position
int SetBit(int num, int pos)
{
	//Check valid position
	if (pos < 0 || pos > 31) return -1;
	//Shift a 1 to desired position and use OR to set bit
	return num |= (1 << pos);
}

//Clears Bit in desired position
int ClearBit(int num, int pos)
{
	//Check valid position
	if (pos < 0 || pos > 31) return -1;
	//Shift 1 to desired position, negate and use AND to keep all bits except the desired bit 
	return num &= ~(1 << pos);
}

//Reverse Bits in num
int Reversbit(int num)
{
	int flipped = 0;
	//length of int is not always defined, get size of int in bytes * 8 bits/byte
	int num_length = sizeof(int) * 8;
	//loop thru every bit
	for (int i = 0;i < num_length;i++)
	{
		flipped <<= 1;
		//Use or on new bit from num
		flipped |= (num & 1);
		num >>= 1;
	}
	return flipped;
}

//return how many bits are set
int CountBit(int num)
{
	int count = 0;
	//length of int is not always defined, get size of int in bytes * 8 bits/byte
	int num_length = sizeof(int) * 8;
	//loop thru every bit
	for (int i = 0;i < num_length;i++)
	{
		//if LSB is set
		if ((num & 1) == 1)
		{
			count++;
		}
		num >>= 1;
	}
	return count;
}

//BOOLEAN whether num is a power of two or not
int PowerofTwo(unsigned int num)
{
	/*
	A number is a power of two if it has only one bit set in binary
	We can find if only one bit was set by performing the AND of num and (num - 1)
		4 (0100) & 3 (0011) = 0
		3 (0011) & 2 (0010) = 2 (0010)
	if the AND of the two = 0, then only one bit was set
	*/
	
	//if num is zero because 0 & (0-1) == 0 but 0 is not a power of two
	if (num == 0) return 0;
	return (num & (num - 1)) == 0;
}

