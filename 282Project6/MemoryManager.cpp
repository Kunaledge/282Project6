#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <iomanip>
#include "MemoryManager.h"

using namespace std;

namespace MemoryManager

{

	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

	//

	// This is the only static memory that you may use, no other global variables

	// may be created, if you need to save data make it fit in MM_pool

	//

	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

	const int MM_POOL_SIZE = 65536;

	char MM_pool[MM_POOL_SIZE];
	unsigned short nextFree;
	unsigned short inUse;
	unsigned short used;

	// I have provided this tool for your use

	void memView(int start, int end)

	{

		const unsigned int SHIFT = 8;

		const unsigned int MASK = 1 << (SHIFT - 1);

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << " Pool Unsignd Unsigned " << endl;

		cout << "Mem Add indx bits chr ASCII# short int " << endl;

		cout << "-------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)

		{

			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal

			cout << '[' << setw(2) << i << ']';	// the index into MM_pool

			value = MM_pool[i];

			cout << " ";

			for (int j = 1; j <= SHIFT; j++)	// the bit sequence for this byte (8 bits)

			{

				cout << ((value & MASK) ? '1' : '0');

				value <<= 1;

			}

			cout << " ";

			cout << '|' << *(char*)(MM_pool + i) << "| (";	// the ASCII character of the 8 bits (1 byte)

			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";	// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";	// the unsigned short value of 16 bits (2 bytes)

			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)


			cout << endl;

		}

	}

	// Initialize set up any data needed to manage the memory pool

	void initializeMemoryManager(void)

	{
		*(unsigned short*) MM_pool = 6;
		*(unsigned short*) nextFree = 6;
		*(unsigned short*) inUse = 0;
		*(unsigned short*) used = 0;

		// your solution goes here

	}

	// return a pointer inside the memory pool

	// If no chunk can accommodate aSize call onOutOfMemory() - still

	void* allocate(int aSize)

	{
		if (freeMemory() < aSize) {
			inUse = nextFree;
			*(unsigned short*)nextFree = 6 + sizeof(aSize);
			*(unsigned short*)MM_pool = nextFree;
			
			return (void*)(MM_pool + *(unsigned short*)MM_pool - aSize);
		}
		else {
			onOutOfMemory();
			return ((void*)inUse);
		}
		// your solution goes here

	}

	// Free up a chunk previously allocated

	void deallocate(void* aPointer)

	{
		used = *(unsigned short*)aPointer;
		unsigned short size = (MM_pool[(char*)aPointer - (char*)MM_pool] + 6);
		for (unsigned int i = 6; i < size; i++) {
			MM_pool[(char*)aPointer - (char*)MM_pool + i] = 0;
		}
		// TODO: IMPLEMENT ME

	}

	//---

	//--- support routines

	//---

	// Will scan the memory pool and return the total free space remaining

	int freeMemory(void)

	{
		return MM_POOL_SIZE - *(unsigned short*)nextFree;
		// your solution goes here

	}

	// Will scan the memory pool and return the total deallocated memory

	int usedMemory(void)

	{
		return MM_POOL_SIZE - freeMemory();
		// your solution goes here

	}

	// Will scan the memory pool and return the total in use memory

	int inUseMemory(void)

	{
		return inUse;
		// your solution goes here

	}

	void onOutOfMemory(void)
	{
	}

	void onOutOfMemory(void* aPointer)
	{
		unsigned short size = (MM_pool[(char*)aPointer - (char*)MM_pool] + 2);
	}


}