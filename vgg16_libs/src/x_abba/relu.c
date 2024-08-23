#include"Definitions_fully_test.h"

void relu(int size, int *input)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (input[j + size*i] < 0) {
				input[j + size*i] = 0;
			}
			else{
				//input[j+size*i]= input[j+size*i]>>12;
				continue;
			}
		}
	}
}

void reluVect(int size, int *input)
{
         for (int i = 0; i < size; i++)
         {
         	if (input[i] < 0) input[i] = 0;
         }

}

// // punt_out = &odds.lay_17[i][0][0];
// // relu_SPM((void*)spmaddrC, (void*)spmaddrC, SIZE_L10_13, (int*) punt_out);

void relu_SPM(void *spm_dest, void *spm_src, int size, int *mem_dest){
	// krelu_v2((void*)spm_dest, (void*)spm_src, size*size*SIZE_OF_INT);//forse questo posso evitare di fare la csr
	int zero=0;
	CSR_MVSIZE(size*size*SIZE_OF_INT);
	krelu((void*)spm_dest, (void*)spm_src);
	kmemstr	((void*)mem_dest,	(void*)spm_dest,	(size*size*SIZE_OF_INT));
	kbcast((void*)spm_dest,(void*)zero);
}


void relu_SPM_fully(void *spm_dest, void *spm_src, int size, int *mem_dest){
	// krelu_v2((void*)spm_dest, (void*)spm_src, size*size*SIZE_OF_INT);//forse questo posso evitare di fare la csr
	int zero=0;
	krelu((void*)spm_dest, (void*)spm_src);
	kmemstr		((void*)mem_dest,	(void*)spm_dest,	(size*SIZE_OF_INT));
	//c'era questa nella versione testata, forse è un bug	CSR_MVSIZE(size*size*SIZE_OF_INT);
	CSR_MVSIZE(size*SIZE_OF_INT);
	kbcast((void*)spm_dest,(void*)zero);
}
