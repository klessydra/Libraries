#include"Definitions_fully_test.h"
															// SPM_C				SPM_A				SPM_B
void convolution2D_SPM(void* spm_dest, void* spm_fm, void* spm_krn, int size)
{
	int print=0;
  //Pointers to Spms and other index that i'll need for the convolution
	void* dest_in_C=(void*)(	(int*)	(spm_dest)	);
  void* dest_in_B=(void*)(	(int*)	(spm_krn)	);
  void* dest_in_D=(void*)(	(int*)	(spmaddrD)	); // NB questo va cambiato, passando il valore così come con gli altri, da direttamente la chiamata, quando avrò
	// aumentato lo spazio delle spm per fare l'esecuzione multitrhead

  int k_element=0;
  int mat_int_shift=0; //internal shifting for properly pointing insied the spms while making kaddv

	int jump_kr_row=3; // determina il salto della riga per la matrice kernel zeropadded
	int kern_offset=0;
	int fm_offset=0;
  int shift_spmB=1;
	
	int bef,act,nex;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*	
	//______________________________sub_kernel F
  CSR_MVSIZE(2*sizeof(int));
	for(int i=1; i< size-1;i++){
		dest_in_C	= (void*)spmaddrC + sizeof(int)*(size*i)+ sizeof(int)*(1)*(size-1);
		dest_in_D	= (void*)spmaddrD + sizeof(int)*(size*i)+ sizeof(int)*(1)*(size-1);
		dest_in_B	= (void*)spmaddrB + sizeof(int)*12*shift_spmB;
		kern_offset	=	0;
		fm_offset= (size-1-1);
		kdotpps_v3(dest_in_D,		(void*)(	(int*)spmaddrA+	(i-1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ), (void*) conv2D_out_scal);
		kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(i)*size				+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
    kaddv(dest_in_D, dest_in_B, dest_in_D);
    kaddv(dest_in_C, dest_in_C, dest_in_D);
		kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(i+1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
		kaddv(dest_in_C, dest_in_C, dest_in_D);
	}
	*/
	
	//______________________________sub_kernel F
  CSR_MVSIZE(8);
		dest_in_B	= (void*)((int*)spm_krn	 + 12*shift_spmB	);
		kern_offset	=	0;
		fm_offset= (size-1-1);
		bef=0;
		act=size;
		nex=size+size;
	for(int i=1; i< size-1;i++){
		dest_in_C	= (void*)((int*)spm_dest + (size*i)+ (1)*(size-1)	);
		dest_in_D	= (void*)((int*)spmaddrD + (size*i)+ (1)*(size-1)	);
		kdotpps_v3	(dest_in_D,		(void*)(	(int*)spm_fm	+	bef			+fm_offset	),	(void*) ( (int*)spm_krn	+			kern_offset ), (void*) conv2D_out_scal);
		kdotpps			(dest_in_B,		(void*)(	(int*)spm_fm	+	act			+fm_offset	),	(void*) ( (int*)spm_krn	+3	+	kern_offset ));
    kaddv				(dest_in_D,		dest_in_B,	dest_in_D);
    kaddv				(dest_in_C,		dest_in_C,	dest_in_D);
		kdotpps			(dest_in_D,		(void*)(	(int*)spm_fm	+	nex			+fm_offset	),	(void*) ( (int*)spm_krn	+6	+	kern_offset ));
		kaddv				(dest_in_C,		dest_in_C,	dest_in_D);
			bef+=size;
			act+=size;
			nex+=size;
	}
	// if(print){
		// printf("Primo ciclo spmC dopo kernel F\n");
		// display_spm_matrix(size,size, (void*)spmaddrC);
	// }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*
	//______________________________sub_kernel___________A-C-G-I
  //______________________________sub_kernel A
	CSR_MVSIZE(2*sizeof(int));
	dest_in_C	=		(void*)spmaddrC + sizeof(int)*(0)*(size-1); //[0]
	dest_in_D	=		(void*)spmaddrD + sizeof(int)*(0)*(size-1);
  dest_in_B	= 	(void*)spmaddrB + sizeof(int)*12*shift_spmB; //shift_spmB=1
    shift_spmB++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(0)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel C
	dest_in_C	=		(void*)spmaddrC + sizeof(int)*(1)*(size-1); //[4]
	dest_in_D	=		(void*)spmaddrD + sizeof(int)*(1)*(size-1);
  dest_in_B	= 	(void*)spmaddrB + sizeof(int)*12*shift_spmB; //shift_spmB=2
    shift_spmB++;
	kern_offset	=	0;
	fm_offset		=	(size-1-1);
	kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(0)*size			+ fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(1)*size			+ fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel G
	dest_in_C	=		(void*)spmaddrC + sizeof(int)*(size)*(size-1); //[20]
	dest_in_D	=		(void*)spmaddrD + sizeof(int)*(size)*(size-1);
  dest_in_B	=		(void*)spmaddrB + sizeof(int)*12*shift_spmB; //shift_spmB=3
    shift_spmB++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(size-1-1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(size-1)	*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	//______________________________sub_kernel I
	dest_in_C	=		(void*)spmaddrC + sizeof(int)*(size+1)*(size-1); //[24]
	dest_in_D	=		(void*)spmaddrD + sizeof(int)*(size+1)*(size-1);
  dest_in_B	= 	(void*)spmaddrB + sizeof(int)*12*shift_spmB; //shift_spmB=4
    shift_spmB++;
	kern_offset	=	0;
	fm_offset		=	(size-1-1);
	kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(size-1-1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(size-1)	*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
	// //______________________________sommo i parziali prodotti dei sub_kernels A-C-G-I
  CSR_MVSIZE(1*sizeof(int));
  kaddv((void*)spmaddrC + sizeof(int)*(0)*(size-1),	    	(void*)spmaddrC + sizeof(int)*(0)*(size-1),	       	(void*)spmaddrD + sizeof(int)*(0)*(size-1));
  kaddv((void*)spmaddrC + sizeof(int)*(1)*(size-1),	    	(void*)spmaddrC + sizeof(int)*(1)*(size-1),        	(void*)spmaddrD + sizeof(int)*(1)*(size-1));
  kaddv((void*)spmaddrC + sizeof(int)*(size)*(size-1),		(void*)spmaddrC + sizeof(int)*(size)*(size-1),  		(void*)spmaddrD + sizeof(int)*(size)*(size-1));
  kaddv((void*)spmaddrC + sizeof(int)*(size+1)*(size-1),	(void*)spmaddrC + sizeof(int)*(size+1)*(size-1),		(void*)spmaddrD + sizeof(int)*(size+1)*(size-1));

  kaddv((void*)spmaddrC + sizeof(int)*(0)*(size-1),	    	(void*)spmaddrC + sizeof(int)*(0)*(size-1),	       	(void*)spmaddrB+sizeof(int)*12*1);
  kaddv((void*)spmaddrC + sizeof(int)*(1)*(size-1),	    	(void*)spmaddrC + sizeof(int)*(1)*(size-1),        	(void*)spmaddrB+sizeof(int)*12*2);
  kaddv((void*)spmaddrC + sizeof(int)*(size)*(size-1),		(void*)spmaddrC + sizeof(int)*(size)*(size-1),  		(void*)spmaddrB+sizeof(int)*12*3);
  kaddv((void*)spmaddrC + sizeof(int)*(size+1)*(size-1),	(void*)spmaddrC + sizeof(int)*(size+1)*(size-1),		(void*)spmaddrB+sizeof(int)*12*4);
	*/
	
	//______________________________sub_kernel___________A-C-G-I
  //______________________________sub_kernel A
	CSR_MVSIZE(8);
	dest_in_C	=		(void*)((int*)spm_dest ); //[0]
	dest_in_D	=		(void*)((int*)spmaddrD );
  dest_in_B	= 	(void*)((int*)spm_krn + 12*shift_spmB); //shift_spmB=1
    shift_spmB++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotpps(dest_in_D,		(void*)(	(int*)spm_fm+				+fm_offset	),	(void*) ( (int*)spm_krn+3+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spm_fm+	size	+fm_offset	),	(void*) ( (int*)spm_krn+6+	kern_offset ));
	//______________________________sub_kernel C
	dest_in_C	=		(void*)((int*)spm_dest + (size-1)	); //[4]
	dest_in_D	=		(void*)((int*)spmaddrD + (size-1)	);
  dest_in_B	= 	(void*)((int*)spm_krn  + 12*shift_spmB); //shift_spmB=2
    shift_spmB++;
	kern_offset	=	0;
	fm_offset		=	(size-1-1);
	kdotpps(dest_in_D,		(void*)(	(int*)spm_fm+				+ fm_offset	),	(void*) ( (int*)spm_krn+3+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spm_fm+	size	+ fm_offset	),	(void*) ( (int*)spm_krn+6+	kern_offset ));
	//______________________________sub_kernel G
	dest_in_C	=		(void*)((int*)spm_dest + (size)*(size-1)	); //[20]
	dest_in_D	=		(void*)((int*)spmaddrD + (size)*(size-1)	);
  dest_in_B	=		(void*)((int*)spm_krn  + 12*shift_spmB); //shift_spmB=3
    shift_spmB++;
	kern_offset	=	1;
	fm_offset		=	0;
	kdotpps(dest_in_D,		(void*)(	(int*)spm_fm+	(size-1-1)*size			+fm_offset	),	(void*) ( (int*)spm_krn		+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spm_fm+	(size-1)	*size			+fm_offset	),	(void*) ( (int*)spm_krn+3	+	kern_offset ));
	//______________________________sub_kernel I
	dest_in_C	=		(void*)((int*)spm_dest + (size+1)*(size-1)	); //[24]
	dest_in_D	=		(void*)((int*)spmaddrD + (size+1)*(size-1)	);
  dest_in_B	= 	(void*)((int*)spm_krn  + 12*shift_spmB	); //shift_spmB=4
    shift_spmB++;
	kern_offset	=	0;
	fm_offset		=	(size-1-1);
	kdotpps(dest_in_D,		(void*)(	(int*)spm_fm+	(size-1-1)*size			+fm_offset	),	(void*) ( (int*)spm_krn		+	kern_offset ));
	kdotpps(dest_in_B,		(void*)(	(int*)spm_fm+	(size-1)	*size			+fm_offset	),	(void*) ( (int*)spm_krn+3	+	kern_offset ));
	// //______________________________sommo i parziali prodotti dei sub_kernels A-C-G-I
  CSR_MVSIZE(4);
  kaddv(	(void*)((int*)spm_dest + (0)*(size-1)				),	(void*)((int*)spm_dest + (0)*(size-1)				),	  (void*)((int*)spmaddrD +(0)*(size-1))				);
  kaddv(	(void*)((int*)spm_dest + (1)*(size-1)				),	(void*)((int*)spm_dest + (1)*(size-1)				),    (void*)((int*)spmaddrD +(1)*(size-1))				);
  kaddv(	(void*)((int*)spm_dest + (size)*(size-1)		),	(void*)((int*)spm_dest + (size)*(size-1)		),  	(void*)((int*)spmaddrD +(size)*(size-1))		);
  kaddv(	(void*)((int*)spm_dest + (size+1)*(size-1)	),	(void*)((int*)spm_dest + (size+1)*(size-1)	),		(void*)((int*)spmaddrD +(size+1)*(size-1))	);

  kaddv(	(void*)((int*)spm_dest + (0)*(size-1)				),	(void*)((int*)spm_dest + (0)*(size-1)				),	 	(void*)((int*)spm_krn+12)	);
  kaddv(	(void*)((int*)spm_dest + (1)*(size-1)				),	(void*)((int*)spm_dest + (1)*(size-1)				),   	(void*)((int*)spm_krn+24)	);
  kaddv(	(void*)((int*)spm_dest + (size)*(size-1)		),	(void*)((int*)spm_dest + (size)*(size-1)		),  	(void*)((int*)spm_krn+36)	);
  kaddv(	(void*)((int*)spm_dest + (size+1)*(size-1)	),	(void*)((int*)spm_dest + (size+1)*(size-1)	),		(void*)((int*)spm_krn+48)	);
	// if(print){	
		// printf("Primo ciclo spmC dopo kernel F-ACGI\n");
		// display_spm_matrix(size,size, (void*)spm_dest);
	// }
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	//______________________________sub_kernel D
  CSR_MVSIZE(2*sizeof(int));
  shift_spmB=1;
	for(int i=1; i< size-1;i++){
		dest_in_C	= (void*)spmaddrC + sizeof(int)*(size*i);
		dest_in_D	= (void*)spmaddrD + sizeof(int)*(size*i);
    dest_in_B	= (void*)spmaddrB + sizeof(int)*12*shift_spmB; //shift_spmB=1
		kern_offset	=	1;
		fm_offset		=	0;
		kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(i-1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(0)*jump_kr_row+	kern_offset ));
		kdotpps(dest_in_B,		(void*)(	(int*)spmaddrA+	(i)*size				+fm_offset	),	(void*) ( (int*)spmaddrB+(1)*jump_kr_row+	kern_offset ));
    kaddv(dest_in_D, dest_in_B, dest_in_D);
    kaddv(dest_in_C, dest_in_C, dest_in_D);
		kdotpps(dest_in_D,		(void*)(	(int*)spmaddrA+	(i+1)*size			+fm_offset	),	(void*) ( (int*)spmaddrB+(2)*jump_kr_row+	kern_offset ));
		kaddv(dest_in_C, dest_in_C, dest_in_D);
	}
	*/
	//______________________________sub_kernel D
  CSR_MVSIZE(8);
  shift_spmB=1;
		kern_offset	=	1;
		fm_offset		=	0;
    dest_in_B	= (void*)((int*)spm_krn  + 12); //shift_spmB=1
		bef=0;
		act=size;
		nex=size+size;
	for(int i=1; i< size-1;i++){
		dest_in_C	= (void*)((int*)spm_dest + (size*i));
		dest_in_D	= (void*)((int*)spmaddrD + (size*i));
		kdotpps			(dest_in_D,		(void*)(	(int*)spm_fm	+	bef			+fm_offset	),	(void*) ( (int*)spm_krn+		kern_offset ));
		kdotpps			(dest_in_B,		(void*)(	(int*)spm_fm	+	act				+fm_offset	),	(void*) ( (int*)spm_krn+3	+	kern_offset ));
    kaddv				(dest_in_D, dest_in_B, dest_in_D);	
    kaddv				(dest_in_C, dest_in_C, dest_in_D);	
		kdotpps			(dest_in_D,		(void*)(	(int*)spm_fm	+	nex			+fm_offset	),	(void*) ( (int*)spm_krn+6	+	kern_offset ));
		kaddv				(dest_in_C, dest_in_C, dest_in_D);
			bef+=size;
			act+=size;
			nex+=size;
	}
	// if(print){
		// printf("Primo ciclo spmC dopo kernel F-ACGI-D\n");
		// display_spm_matrix(size,size, (void*)spmaddrC);
  // }

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	//______________________________sub_kernel E
  CSR_MVSIZE((size-2)*sizeof(int));
	for(int i=1; i< size-1;i++)
	{
		// dest_in_C	= (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int);
		// dest_in_D	= (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int);
		k_element=0;
		for (int rw_pt=-1; rw_pt<2; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
		//instead of making 9 different ksvmulrf
		{
			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*size	+0 ),
                (void*)	( (int*)spmaddrB+k_element++) );
								
				ksrav((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(int*)conv2D_out_scal);
								
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int));

			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*size	+1 ),
                (void*)	( (int*)spmaddrB+k_element++) );
				
				ksrav((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(int*)conv2D_out_scal);
								
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int));

			ksvmulsc((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
        			  (void*)	( (int*)spmaddrA + (i+rw_pt)*size	+2 ),
                (void*)	( (int*)spmaddrB+k_element++) );
								
				ksrav((void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int),
								(int*)conv2D_out_scal);
								
  		kaddv ((void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int),
              (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int));
		}
	}
	*/
  //______________________________sub_kernel E
  CSR_MVSIZE((size-2)*4);
		bef=0;
		act=size;
		nex=size+size;
	for(int i=1; i< size-1;i++)
	{
		// dest_in_C	= (void*)(	(int*)	(spmaddrC)	) + sizeof(int)*(size*i)+1*sizeof(int);
		// dest_in_D	= (void*)(	(int*)	(spmaddrD)	) + sizeof(int)*(size*i)+1*sizeof(int);
		k_element=0;
		for (int rw_pt=-1; rw_pt<2; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
		//instead of making 9 different ksvmulrf
		{
			ksvmulsc(	(void*)	(	(int*)(spmaddrD)	+ 	act+1	),
									(void*)	( (int*)spm_fm 			+ 	(i+rw_pt)*size	+0 ),
									(void*)	( (int*)spm_krn			+		k_element++) );
								
				ksrav(	(void*)(	(int*)	(spmaddrD)	 + act+1	),
									(void*)(	(int*)	(spmaddrD)	 + act+1	),
									(int*)conv2D_out_scal);
								
  		kaddv (	(void*)(	(int*)	(spm_dest)	 + act+1)	,
								(void*)(	(int*)	(spm_dest)	 + act+1)	,
								(void*)(	(int*)	(spmaddrD)	 + act+1)	);

			ksvmulsc(	(void*)	(	(int*)(spmaddrD)	+ 	act+1	),
									(void*)	( (int*)spm_fm 			+ 	(i+rw_pt)*size	+1 ),
									(void*)	( (int*)spm_krn			+		k_element++) );
				
				ksrav(	(void*)(	(int*)	(spmaddrD)	 + act+1	),
									(void*)(	(int*)	(spmaddrD)	 + act+1	),
									(int*)conv2D_out_scal);
								
  		kaddv (	(void*)(	(int*)	(spm_dest)	+ act+1)	,
								(void*)(	(int*)	(spm_dest)	+ act+1)	,
								(void*)(	(int*)	(spmaddrD)	+ act+1)	);

			ksvmulsc(	(void*)(	(int*)(spmaddrD)	+ act+1	),
									(void*)	( (int*)spm_fm 			+ (i+rw_pt)*size	+2 ),
									(void*)	( (int*)spm_krn			+ k_element++) );
								
				ksrav((void*)(	(int*)	(spmaddrD)	 + act+1	),
								(void*)(	(int*)	(spmaddrD)	 + act+1	),
								(int*)conv2D_out_scal);
								
  		kaddv (	(void*)(	(int*)	(spm_dest)	+ act+1)	,
								(void*)(	(int*)	(spm_dest)	+ act+1)	,
								(void*)(	(int*)	(spmaddrD)	+ act+1)	);
		}
			act+=size;
	}
	// if(print){
		// printf("Primo ciclo spmC dopo kernel F-ACGI-D-E\n");
		// display_spm_matrix(size,size, (void*)spmaddrC);
  // }

	

  // //______________________________sub_kernel B
  CSR_MVSIZE((size-2)*4);
		bef=0;
		act=size;
		nex=size+size;
  for(int i=0; i< 1;i++)
  {
    dest_in_C	= (void*)((int*)spm_dest  + 1	);
    dest_in_D	= (void*)((int*)spmaddrD  + 1	);
    k_element=3;
    for (int rw_pt=0; rw_pt<2; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
    //instead of making 9 different ksvmulrf
    {
      ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+0 ),	(void*)	( (int*)spm_krn+k_element++) );
					ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv (dest_in_C, dest_in_C,  dest_in_D);
			
      ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+1 ),	(void*)	( (int*)spm_krn+k_element++) );
					ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv	(dest_in_C, dest_in_C,  dest_in_D);
			
      ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+2 ),	(void*)	( (int*)spm_krn+k_element++) );
					ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv (dest_in_C, dest_in_C,  dest_in_D);
    }
  }
	// if(print){
		// printf("Primo ciclo spmC dopo kernel F-ACGI-D-E-B\n");
		// display_spm_matrix(size,size, (void*)spmaddrC);
  // }

	
	
	//______________________________sub_kernel H
  CSR_MVSIZE((size-2)*4);
		bef=0;
		act=size;
		nex=size+size;
	for(int i=size-1; i< size;i++)
	{
		dest_in_C	= (void*)((int*)spm_dest + (size*i)+1);
    dest_in_D	= (void*)((int*)spmaddrD + (size*i)+1);
		k_element=0;
		for (int rw_pt=-1; rw_pt<1; rw_pt++) //rw_pt is an index i use to point to the correct row, regarding this loop that is executed three times
		//instead of making 9 different ksvmulrf
		{
			ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+0 ),	(void*)	( (int*)spm_krn+k_element++) );
				ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
			
			ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+1 ),	(void*)	( (int*)spm_krn+k_element++) );
				ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
			
			ksvmulsc(dest_in_D,			(void*)	( (int*)spm_fm + (i+rw_pt)*size	+2 ),	(void*)	( (int*)spm_krn+k_element++) );
				ksrav(dest_in_D,	dest_in_D,	(int*)conv2D_out_scal);
      kaddv	(dest_in_C, dest_in_C, dest_in_D);
		}
	}
	// if(print){
		// printf("Primo ciclo spmC dopo kernel F-ACGI-D-E-B-H\n");
		// display_spm_matrix(size,size, (void*)spmaddrC);
	// }

	
	CSR_MVSIZE(SIZE_L1_2*SIZE_L1_2*sizeof(int));	
	shift_spmB=0;
	kbcast((void*)spmaddrD,(void*)shift_spmB);
	// kbcast((void*)spmaddrB,(void*)shift_spmB);
}


