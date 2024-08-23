#include"Definitions_fully_test.h"
// Main approach
void addBias(int size, int *matrix, int bias)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[j + size*i] += bias;
		}
	}
}
// DSP approach 
void addBias_SPM(void *spm_dest,void *spm_src,void *spm_bias, int size)
{
	ksvaddsc_v2((void*)spm_dest,(void*)spm_src,(void*)(spm_bias),size*size*SIZE_OF_INT);
	//ksvaddsc32((void*)spm_dest,(void*)spm_src,(void*)(spm_bias+12*sizeof(int)));
}

