#include<stdlib.h>
#include<stdio.h>

extern const float input[3][32][32];
void scan(float *arr,int ch,int i, int j){
	int i;
	int dim=ch*i*j;
	float min=0;
	float max=0;
	float read;
	for(i=0;i<dim;i++){
		read=arr[i];
		if(read<min){
			min=read;
		}
		if(read>max){
			max=read;
		}
	}
	printf("max=%f\nmin=%d\n",max,min);
};
int main()
{
	scan(&input,3,32,32);
	return 0;
}
