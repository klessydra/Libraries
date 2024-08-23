#include"Definitions_fully_test.h"
//######  ######   #####                                                             
//#     # #     # #     #         #    #  ####  #####  ###### #       ####  # #    # 
//#     # #     # #               ##  ## #    # #    # #      #      #      # ##  ## 
//#     # ######  #  ####         # ## # #    # #    # #####  #       ####  # # ## # 
//#     # #     # #     #         #    # #    # #    # #      #           # # #    # 
//#     # #     # #     #         #    # #    # #    # #      #      #    # # #    # 
//######  ######   #####          #    #  ####  #####  ###### ######  ####  # #    # 
//                        #######
void printmod_sel(int layer,int ch, int dim_i, int dim_j, int *input,int shift)
//this will print on Transcript only the specified slice of the matrix: E.g. ch=64 will print matrix[63]
{
	int k,i,j;
	k=ch-1; //per stampare proprio la matrice selezionata
	printf("DBG_print_sel:\tOUTPUT_%d_layer_%d\n",ch,layer);
	for (i = 0; i < dim_i; i++)
	{
		for (j = 0; j < dim_j; j++)
		{
			printf("\t%d", (int)(((float)(input[k*dim_i*dim_j+i*dim_j+j]))/pow(2,shift)));
		} 
		printf("\n");
	}	
}
void printmod_full(int layer,int ch, int dim_i, int dim_j, int *input, int shift) 
//this will print on Transcript the whole matrix
{
	int k,i,j;
	printf("DBG_print_full:\tOUTPUT_completo_layer_%d\n",layer);
	for (k = 0; k < ch; k++)
	{
		for (i = 0; i < dim_i; i++)
		{
			for (j = 0; j < dim_j; j++)
			{
				printf("%d ", (int)(((float)(input[k*dim_i*dim_j+i*dim_j+j]))/pow(2,shift)));
			} 
			printf("\n");
		}
	}	
}
void dbg_count_zero(int ch, int dim_i, int dim_j,int *input)
{
	int counter=0;
	int k,i,j;
	for (k = 0; k < ch; k++)
	{
		for (i = 0; i < dim_i; i++)
		{
			for (j = 0; j < dim_j; j++)
			{
				if((int)input[ k*dim_i*dim_j + i*dim_j + j] == 0)
				{
					counter++;
				}
			} 
		}
	}
	printf("DBG_Counter:%d\n",counter);
}
void spegni_threads()
{
	for (int i=0;i<5;i++)
	{
		if (Klessydra_get_coreID()==0);
		else
		{
			Klessydra_WFI();
		}
	}
  printf("\n---Mode:Single Thread_0---\n");
}
void display_spm_matrix(int size_r,int size_c,void* pt_spm_mat)
{
  printf("\n--------------------------------------\n");
  printf("\t\t-------Display_matrix-----\n");
  int pref_buff[32*32]={0};
  kmemstr((int*)pref_buff, (void*)(pt_spm_mat), (size_r*size_c)*sizeof(int));
  for(int i=0; i<size_r; i++)
  {
    for(int j=0; j<size_c; j++)
    {
      printf("\t%d",pref_buff[i*size_r+j]);
    }
    printf("\n");
  }
  printf("\t\t-------Display_matrix-----\n");
  printf("--------------------------------------\n\n");
}
void display_spm_matrix_scal(int ch, int size_r,int size_c,void* pt_spm_mat, int shift)
{
  printf("\n--------------------------------------\n");
  printf("\t\t-------Display_matrix-----\n");
	int k=0;
  int pref_buff[32*32]={0};
  kmemstr((int*)pref_buff, (void*)((int*)pt_spm_mat + k*size_r*size_c), (size_r*size_c)*sizeof(int));
  for(int i=0; i<size_r; i++)
  {
    for(int j=0; j<size_c; j++)
    {
			printf("\t%d", (int)(((float)(pref_buff[i*size_r+j]))/pow(2,shift)));
      // printf("\t%d", (	(pref_buff[i*size_r+j])	>>	prnt_sc	)		);
    }
    printf("\n");
  }
  printf("\t\t-------Display_matrix-----\n");
  printf("--------------------------------------\n\n");
}
void isequal(int row, int col, int *pt1, int *pt2)
{
	int err=0;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if( *((int*)pt1+i*row+j) != *((int*)pt2+i*row+j) )
			{
				printf("\nERROR at elements [%d][%d] !\n",i+1,j+1);
        err++;
			}
		}
	}
  if (err==0){
    printf("No errors.\n");
  }
}