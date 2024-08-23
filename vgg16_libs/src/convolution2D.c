#include"Definitions_fully_test.h"

void convolution2D(int size, int (*matrix)[size], int *kernel_tmp, int *out) {
    //printf("DBG_sono dentro la CONV FULLY_fixed_point!\n");
	int kernel[9];
	for(int i=0;i<9;i++){
    	kernel[i]=(kernel_tmp[i]>>conv2D_scaling_factor);
    }
	int i, j;				
	int pt=0;
	int zeropad[34][34]={0};
	int mono=0;

	for (int i=1; i< size+2-1; i++)
		for (int j=1; j< size+2-1; j++)
			zeropad[i][j]=matrix[i-1][j-1];

	for (i = 1; i < (size+2)-1; i++)
	{
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i-1][j-1]>>conv2D_scaling_factor) 	* kernel[0])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i-1][j]	>>conv2D_scaling_factor)	* kernel[1])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i-1][j+1]>>conv2D_scaling_factor)	* kernel[2])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i][j-1]	>>conv2D_scaling_factor)	* kernel[3])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i][j]	>>conv2D_scaling_factor)		* kernel[4])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i][j+1]	>>conv2D_scaling_factor)	* kernel[5])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i+1][j-1]>>conv2D_scaling_factor) 	* kernel[6])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i+1][j] >>conv2D_scaling_factor)		* kernel[7])	>>		conv2D_out_scal ;
		}
		for (j = 1; j < (size+2)-1; j++){
			out[(i-1)*size+(j-1)] +=	(	(zeropad[i+1][j+1]>>conv2D_scaling_factor) 	* kernel[8])	>>		conv2D_out_scal ;
		}
	}
	
}

