#include "Definitions_fully_test.h"

void softmax (int dim, int *input, float *output)
{//								odds.lay_19		even.lay_22
 	int SUM = 0;
	//float vect_float[dim];
	float ftmp;
	//printf("\n------Conversione da integer a float, facendo cast a float e dividendo per /2^21\n");

	for (int i=0;i<dim;i++){
		// ftmp=((float)(input[i]))/pow(2,layer_0_conv_rate);
		ftmp=((float)(input[i])) / 2097152 ;
		output[i]=ftmp;
		//printf("{%d}\t Entra= %9d\t Esce_float= NaN\t== 0x%08x\n",i,	input[i],	*(int*)(&output[i]));
	}
	
	printf("\n------Incremento SUM a colpi di exp(output(i))\n");
	for (int i = 0; i < dim; i++)
	{
			//printf("{%d}\t SUM = %d = 0x%08X\t",i,SUM,SUM);
		SUM = SUM + expf(output[i]);
			appoggio_exp = expf(output[i]);
			//printf("incremento = NaN = 0x%08X\n",	*(int*)&appoggio_exp	);
	}
	
	printf("\n------Calclo le 10 uscite facendo exp(output)/SUM\n");
	for (int i = 0; i < dim; i++)
	{
		output[i] = expf(output[i])/SUM ;
		//printf("{%d}\t output = 0x%08X\n",i,*(int*)(&output[i]));
	}
	//printf("\n");
}

