#include"Definitions_fully_test.h"

void convolution2D_SPM(void* spm_dest, void* spm_fm, void* spm_krn, int mat_size)
{
	int print=0;
	int size=mat_size; //si riferisce alla matrice in input
	void* dest_in_C_zero=(void*)(	(int*)(spmaddrC)	);
	void* dest_in_B_zero=(void*)(	(int*)(spmaddrB)	);
	void* dest_in_D_zero=(void*)(	(int*)(spmaddrD)	);
  //Pointers to Spms and other index that i'll need for the convolution
	void* dest_in_C=(void*)(	(int*)	(spmaddrC)	);
  void* dest_in_B=(void*)(	(int*)	(spmaddrB)	);
  void* dest_in_D=(void*)(	(int*)	(spmaddrD)	);

  int k_element=0;
  int mat_int_shift=0; //internal shifting for properly pointing insied the spms while making kaddv

	int jump_fm_row=mat_size; // determina il salto della ·matrice zeropadded
	int jump_kr_row=3; // determina il salto della riga per la matrice kernel zeropadded
	int kern_offset=0;
	int fm_offset=0;
  int move_b_pt=1;
	
	//______________________________sub_kernel F
	//resetti matrice D preventivamente
  // CSR_MVSIZE((A_ORDER*A_ORDER)*sizeof(int));
  // ksvmulrf((void*)spmaddrD,			(void*)	( (int*)spmaddrB ),	(void*)((int*)single_value_zero));
  CSR_MVSIZE(2*sizeof(int));
	for(int i=1; i< size-1;i++){
		dest_in_C	= dest_in_C_zero + sizeof(int)*(mat_size*i)+ sizeof(int)*(1)*(jump_fm_row-1);
		dest_in_D	= dest_in_D_zero + sizeof(int)*(mat_size*i)+ sizeof(int)*(1)*(jump_fm_row-1);
		dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt;
		kern_offset	=	0;
		fm_offset= (jump_fm_row-1-1);
		kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(i-1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
		kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(i)*jump_fm_row				+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
    kaddv(dest_in_D, dest_in_B, dest_in_D);
    kaddv(dest_in_C, dest_in_C, dest_in_D);
		kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(i+1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
		kaddv(dest_in_C, dest_in_C, dest_in_D);
	}
	if(print){
		printf("Primo ciclo spmC dopo kernel F\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
	}
  // display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);

  //______________________________sub_kernel___________A-C-G-I
  //______________________________sub_kernel A
	CSR_MVSIZE(2*sizeof(int));
	dest_in_C	=		dest_in_C_zero + sizeof(int)*(0)*(jump_fm_row-1); //[0]
	dest_in_D	=		dest_in_D_zero + sizeof(int)*(0)*(jump_fm_row-1);
  dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt; //move_b_pt=1
    move_b_pt++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(0)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel C
	dest_in_C	=		dest_in_C_zero + sizeof(int)*(1)*(jump_fm_row-1); //[4]
	dest_in_D	=		dest_in_D_zero + sizeof(int)*(1)*(jump_fm_row-1);
  dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt; //move_b_pt=2
    move_b_pt++;
	kern_offset	=	0;
	fm_offset		=	(jump_fm_row-1-1);
	kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(0)*jump_fm_row			+ fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(1)*jump_fm_row			+ fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel G
	dest_in_C	=		dest_in_C_zero + sizeof(int)*(size)*(jump_fm_row-1); //[20]
	dest_in_D	=		dest_in_D_zero + sizeof(int)*(size)*(jump_fm_row-1);
  dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt; //move_b_pt=3
    move_b_pt++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(size-1-1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
	kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(size-1)	*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel I
	dest_in_C	=		dest_in_C_zero + sizeof(int)*(size+1)*(jump_fm_row-1); //[24]
	dest_in_D	=		dest_in_D_zero + sizeof(int)*(size+1)*(jump_fm_row-1);
  dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt; //move_b_pt=4
    move_b_pt++;
	kern_offset	=	0;
	fm_offset		=	(jump_fm_row-1-1);
	kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(size-1-1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
	kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(size-1)	*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	// //______________________________sommo i parziali prodotti dei sub_kernels A-C-G-I
	// CSR_MVSIZE(size*size*sizeof(int));
	// kaddv(dest_in_C_zero,		dest_in_C_zero,		dest_in_D_zero);
  // // display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrC);
  // // display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);
  // //______________________________sommo i parziali prodotti dei sub_kernels A-C-G-I
  CSR_MVSIZE(1*sizeof(int));
  kaddv(dest_in_C_zero + sizeof(int)*(0)*(jump_fm_row-1),	    	dest_in_C_zero + sizeof(int)*(0)*(jump_fm_row-1),	       	dest_in_D_zero + sizeof(int)*(0)*(jump_fm_row-1));
  kaddv(dest_in_C_zero + sizeof(int)*(1)*(jump_fm_row-1),	    	dest_in_C_zero + sizeof(int)*(1)*(jump_fm_row-1),        	dest_in_D_zero + sizeof(int)*(1)*(jump_fm_row-1));
  kaddv(dest_in_C_zero + sizeof(int)*(size)*(jump_fm_row-1),		dest_in_C_zero + sizeof(int)*(size)*(jump_fm_row-1),  		dest_in_D_zero + sizeof(int)*(size)*(jump_fm_row-1));
  kaddv(dest_in_C_zero + sizeof(int)*(size+1)*(jump_fm_row-1),	dest_in_C_zero + sizeof(int)*(size+1)*(jump_fm_row-1),		dest_in_D_zero + sizeof(int)*(size+1)*(jump_fm_row-1));

  kaddv(dest_in_C_zero + sizeof(int)*(0)*(jump_fm_row-1),	    	dest_in_C_zero + sizeof(int)*(0)*(jump_fm_row-1),	       	dest_in_B_zero+sizeof(int)*12*1);
  kaddv(dest_in_C_zero + sizeof(int)*(1)*(jump_fm_row-1),	    	dest_in_C_zero + sizeof(int)*(1)*(jump_fm_row-1),        	dest_in_B_zero+sizeof(int)*12*2);
  kaddv(dest_in_C_zero + sizeof(int)*(size)*(jump_fm_row-1),		dest_in_C_zero + sizeof(int)*(size)*(jump_fm_row-1),  		dest_in_B_zero+sizeof(int)*12*3);
  kaddv(dest_in_C_zero + sizeof(int)*(size+1)*(jump_fm_row-1),	dest_in_C_zero + sizeof(int)*(size+1)*(jump_fm_row-1),		dest_in_B_zero+sizeof(int)*12*4);
	if(print){
		printf("Primo ciclo spmC dopo kernel F-ACGI\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
	}
	//______________________________sub_kernel D
	//resetti matrice D preventivamente
  // CSR_MVSIZE((A_ORDER*A_ORDER)*sizeof(int));
  // ksvmulrf((void*)spmaddrD,			(void*)	( (int*)spmaddrB ),	(void*)((int*)single_value_zero));
  CSR_MVSIZE(2*sizeof(int));
  move_b_pt=1;
	for(int i=1; i< size-1;i++){
		dest_in_C	= dest_in_C_zero + sizeof(int)*(mat_size*i);
		dest_in_D	= dest_in_D_zero + sizeof(int)*(mat_size*i);
    dest_in_B	= dest_in_B_zero + sizeof(int)*12*move_b_pt; //move_b_pt=1
		kern_offset	=	1;
		fm_offset		=	0;
		kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(i-1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
		kdotp32(dest_in_B,		(void*)(	(int*)spmaddrA+	(i)*jump_fm_row				+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
    kaddv(dest_in_D, dest_in_B, dest_in_D);
    kaddv(dest_in_C, dest_in_C, dest_in_D);
		kdotp32(dest_in_D,		(void*)(	(int*)spmaddrA+	(i+1)*jump_fm_row			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
		kaddv(dest_in_C, dest_in_C, dest_in_D);
	}
	if(print){
		printf("Primo ciclo spmC dopo kernel F-ACGI-D\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
  }
	// display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);

  //______________________________sub_kernel E
	//resetti matrice D preventivamente
  // CSR_MVSIZE((A_ORDER*A_ORDER)*sizeof(int));
  // ksvmulrf((void*)spmaddrD,			(void*)	( (int*)spmaddrB ),	(void*)((int*)single_value_zero));
  CSR_MVSIZE((size-2)*sizeof(int));
	for(int i=1; i< size-1;i++)
	{
		// dest_in_C	= (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(A_ORDER*i)+1*sizeof(int);
		// dest_in_D	= (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(A_ORDER*i)+1*sizeof(int);
		k_element=0;
		for (int rw_pt=-1; rw_pt<2; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
		//instead of making 9 different ksvmulrf
		{
			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+0 ),
                (void*)	( (int*)spmaddrB+k_element++) );
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int));

			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+1 ),
                (void*)	( (int*)spmaddrB+k_element++) );
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int));

			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+2 ),
                (void*)	( (int*)spmaddrB+k_element++) );
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(mat_size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(mat_size*i)+1*sizeof(int));
		}
	}
	if(print){
		printf("Primo ciclo spmC dopo kernel F-ACGI-D-E\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
  }
	// display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);


  // //______________________________sub_kernel B
  // //resetti matrice D preventivamente
  // CSR_MVSIZE((A_ORDER*A_ORDER)*sizeof(int));
  // ksvmulrf((void*)spmaddrD,			(void*)	( (int*)spmaddrB ),	(void*)((int*)single_value_zero));
  CSR_MVSIZE((size-2)*sizeof(int));
  for(int i=0; i< 1;i++)
  {
    dest_in_C	= dest_in_C_zero  + 1*sizeof(int);
    dest_in_D	= dest_in_D_zero  + 1*sizeof(int);
    k_element=3;
    for (int rw_pt=0; rw_pt<2; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
    //instead of making 9 different ksvmulrf
    {
      ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+0 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv (dest_in_C, dest_in_C,  dest_in_D);
      ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+1 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv	(dest_in_C, dest_in_C,  dest_in_D);
      ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+2 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv (dest_in_C, dest_in_C,  dest_in_D);

    }
  }
	if(print){
		printf("Primo ciclo spmC dopo kernel F-ACGI-D-E-B\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
  }
	// display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);

	//______________________________sub_kernel H
	//resetti matrice D preventivamente
  // CSR_MVSIZE((A_ORDER*A_ORDER)*sizeof(int));
  // ksvmulrf((void*)spmaddrD,			(void*)	( (int*)spmaddrB ),	(void*)((int*)single_value_zero));
  CSR_MVSIZE((size-2)*sizeof(int));
	for(int i=size-1; i< size;i++)
	{
		dest_in_C	= dest_in_C_zero + sizeof(int)*(mat_size*i)+1*sizeof(int);
    dest_in_D	= dest_in_D_zero + sizeof(int)*(mat_size*i)+1*sizeof(int);
		k_element=0;
		for (int rw_pt=-1; rw_pt<1; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
		//instead of making 9 different ksvmulrf
		{
			ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+0 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
			ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+1 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
			ksvmulsc(dest_in_D,			(void*)	( (int*)spmaddrA + (i+rw_pt)*jump_fm_row	+2 ),	(void*)	( (int*)spmaddrB+k_element++) );
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
		}
	}
	if(print){
		printf("Primo ciclo spmC dopo kernel F-ACGI-D-E-B-H\n");
		display_spm_matrix(size,size, (void*)spmaddrC);
	}
  // display_spm_matrix(A_ORDER,A_ORDER, (void*)spmaddrD);

}