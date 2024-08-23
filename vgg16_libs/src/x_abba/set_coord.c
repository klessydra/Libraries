#include"Definitions_fully_test.h"

void set_coord(int a,int b, int c, int d, int e){
	layer_0_conv_rate=	a;
	getWe_conv_rate=	b;
	conv2D_scaling_factor=	c;
	getBi_conv_rate=	d;
	print_scaling_factor=	e;
  printf("---------detnro la funzione set_coord--------\n");
  printf("address of layer_0_conv_rate=%p\tval=%d\n",(void*)&layer_0_conv_rate,layer_0_conv_rate);
  printf("address of getWe_conv_rate=%p\tval=%d\n",(void*)&getWe_conv_rate,getWe_conv_rate);
  printf("address of conv2D_scaling_factor=%p\tval=%d\n",(void*)&conv2D_scaling_factor,conv2D_scaling_factor);
  printf("address of getBi_conv_rate=%p\tval=%d\n",(void*)&getBi_conv_rate,getBi_conv_rate);
  printf("address of print_scaling_factor=%p\tval=%d\n",(void*)&print_scaling_factor,print_scaling_factor); 
}
