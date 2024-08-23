#include"Definitions_fully_test.h"

void getFeatures_SPM(void* spm_dest,  int size, int (*pt_to_fm)[size])
{ 
	kmemld		((void*)spm_dest,	(void*)(pt_to_fm),	(size*size*SIZE_OF_INT));


	

	//per debuggare lay15
	//display_spm_matrix(size,size,(void*)spm_dest);

	//se la CSR MVSIZE la porto all'esterno uso la versione V1
	ksrav_v2((void*)spm_dest,(void*)spm_dest,(int*)conv2D_scaling_factor,(size*size*SIZE_OF_INT));
	


	//ksrav((void*)spm_dest,(void*)spm_dest,(int*)conv2D_scaling_factor);
	//mv_fl++;
	
	// for(int ii=	0;ii<size;ii++){ 
		// for (int jj=0; jj<size; jj++){
			// printf("%d\t",pt_to_fm[ii][jj]);
		// }
		// printf("\n");
	// }
	// printf("\n");
}

void getFeatures_SPM_fully(void* spm_dest,  int size, int *pt_to_fm)
{
	kmemld		((void*)spm_dest,	(void*)(pt_to_fm),	(size*SIZE_OF_INT)	);
	ksrav_v2((void*)spm_dest,	(void*)spm_dest,		(int*)conv2D_scaling_factor,	(size*SIZE_OF_INT)	);
}
 
