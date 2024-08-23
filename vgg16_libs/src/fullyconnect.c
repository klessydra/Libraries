#include"Definitions_fully_test.h"

int fullyconnect(int dim, int *a, int *b)
{
    int temp_sum = 0;
	int tmp1,tmp2;
		for(int i=0; i<dim ; i++){
			tmp1=(a[i]>>conv2D_scaling_factor);
			tmp2=b[i]>>conv2D_scaling_factor;
			temp_sum += ((tmp1*tmp2)>>conv2D_out_scal);
		}
	return temp_sum;
}

void fullyconnect_SPM(void *spm_dest, void *spm_src1, void *spm_src2,int dim)
{
		// CSR_MVSIZE(dim*sizeof(int));
		// CSR_MVSIZE(1*sizeof(int));
		
		// No scaling factor
		// kdotp32( (void*)spm_dest,	(void *)( (int*)spm_src1),	 (void*)( (int*) spm_src2) );
			
		// Scaling factor enabled
		kdotpps( (void*)spm_dest,	(void *)( (int*)spm_src1),	 (void*)( (int*) spm_src2) );
		
}
