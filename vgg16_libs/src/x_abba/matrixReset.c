#include"Definitions_fully_test.h"

void matrixReset(int size, int *matrix)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[j + size*i] = 0;
		}
	}
}

// void matrixReset_SPM(int *mem_dest, void* smp_src_clean, int stride,int size)
// {	
	// kmemstr((void*)(mem_dest+stride*(size*size)),	(void*)smp_src_clean,	(size*size*sizeof(int)));
// }