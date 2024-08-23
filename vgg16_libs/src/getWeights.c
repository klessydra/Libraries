#include"Definitions_fully_test.h"
// Main approach
void getWeights(const int *fp, int num_param, int *kernel, int cont)
{
	/*
	for (int index=0; index<num_param; index++){
		kernel[index] = to_int32(fp[(cont*num_param)+index],getWe_conv_rate);
		//printf("fp[%d]\n",(cont*9)+ind);
	}
	*/
	for (int ind=0; ind<num_param; ind++){
		kernel[ind] = fp[(cont*num_param)+ind];
		//printf("fp[%d]\n",(cont*9)+ind);
	}
}
 
 
// DSP approach
void getWeights_SPM(void* spm_dest, const int *pt_to_wh, int num_param, int offset)
{
	kmemld((void*)spm_dest,	(void*)((int*)pt_to_wh+(offset*num_param)),	(num_param*1*SIZE_OF_INT));
		
		// for(int i=0;i<3;i++){
				// for(int j=0;j<3;j++){
					// printf("%d\t",*(pt_to_wh+(offset*num_param)+i*3+j));
				// }printf("\n");
			// }printf("\n");
	
			// con quella che segue provavo ad abbandonare l'uso dell'offset*num_param, ma non ci riesco
			// kmemld((void*)spm_dest,	(void*)((int*)pt_to_wh),	(num_param*SIZE_OF_INT));
			//display_spm_matrix(3,3,(void*)spm_dest);
			// printf("offset_getweights=%d\n",(offset*num_param));
			// ksrav_v2((void*)spm_dest,(void*)spm_dest,(int*)conv2D_scaling_factor,(num_param*1*SIZE_OF_INT));
	
	
	//per debuggare lay15
	if(stampadbg==1)	{
		display_spm_matrix(3,3,(void*)spm_dest);
	}


	//se porto al'esterno la csr per farne di meno
	CSR_MVSIZE(num_param*1*SIZE_OF_INT);
	ksrav((void*)spm_dest,(void*)spm_dest,(int*)conv2D_scaling_factor);
	mv_fl++;
	
	
	
	// //printf("getW punta @=%p\n",(int*)pt_to_wh+(offset*num_param));
	// for(int k=0;k<num_param;k++){	
		// printf("dentro getW (base+%d*%d+%d)=%d\n",offset,num_param,k,*((int*)pt_to_wh+(offset*num_param+k)));
	// }

	// // int k=0;
	// // printf("-------------Dentro getW_SPM, cont=%d\n",offset);
	// // for(int i=0;i<3;i++){ 
		// // for (int j=0; j<3; j++){
			// // printf("%d\t",*((int*)pt_to_wh+(offset*num_param+k)));
			// // k++;
		// // }printf("\n");
	// // }printf("\n");	
}
