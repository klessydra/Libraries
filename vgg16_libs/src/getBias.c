#include"Definitions_fully_test.h"
// Main approach
int getBias(const int *ptb,int cont)
{
    //printf("DBG: layer %d; done output=%d\n",(lt+1),(cont+1));
    	/*
	int bias;
	bias=to_int32(ptb[cont],getBi_conv_rate);
	return bias;
	*/
	return ptb[cont];
}
 
// DSP approach
void getBias_SPM(void *spm_dest, const int *pt_to_bs,int offset)
{
	// return ptb[offset];
	// printf("bias letto:%d\n",ptb[offset]);
	// printf("offset_bias=%d\n",offset);
	// display_spm_matrix(1,1,(void*)(spm_dest+12*sizeof(int)));

	kmemld((void*)(spm_dest),	(void*)(pt_to_bs+offset),	(1*SIZE_OF_INT));
	mv_bs++;
}

void getBias_SPM_fully(void *spm_dest, const int *pt_to_bs,int offset, int size){
	kmemld((void*)spm_dest,	(void*)(pt_to_bs+offset*(size)),	(size*sizeof(int)));
	//mv_bs++;
}
