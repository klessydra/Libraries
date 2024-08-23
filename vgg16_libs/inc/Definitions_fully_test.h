#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "dsp_functions.h"
#include "functions.h"
#include "klessydra_defs.h"

#define INPUT_SIZE 32
#define CHANNEL_SIZE 3
#define SIZE_L1_2 INPUT_SIZE
#define SIZE_L3_5 INPUT_SIZE/2
#define SIZE_L6_9 INPUT_SIZE/4
#define SIZE_L10_13 INPUT_SIZE/8
#define SIZE_L14_17 INPUT_SIZE/16
#define SIZE_L18 INPUT_SIZE/32
#define OUTPUT_SIZE 10
#define SIZE_OF_INT 4
extern float appoggio_exp;
extern int stampadbg;

extern int print_global_dbg;
extern int print_global_id;
extern int print_global_k;
static unsigned long int tensor_load[3];
extern int memld_count[3];
extern int memld_width[3];
extern int memst_count[3];
extern int memst_width[3];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int layer_0_conv_rate=21; //questo non ricordo bene a che serve
static int getWe_conv_rate=21;
static int getBi_conv_rate=21;

static int print_scaling_factor=21; //per printare i valori in integer che siano anche rappresentativi di dove è la virgola fissa
//questi sono rispettivamente il pre ed il post scaling factor delle mie vecchie convolution2D
static int conv2D_scaling_factor=8;
static int conv2D_out_scal=5;
//NB 29_03: dovendo simulare su T13, dove non ho ancora supporto ad un postScaling factor all'interno della convolution2D, adesso cambio il
// valore della conv2D_out_scal=5 portandolo 0, così da fare poi una stampa piccola del primo output atteso dalla rete al layer 1
// quando però la convoluzione la faccio decisamente ridotta: stampo così su transcript il valore atteso SENZA alcun post scaling factor
// durante la stampa: così ho un benchmark per verificare se poi la stessa convoluzione, seppur minima, mi riesca con l'uso delle SPM+DSP
extern int mv_fl, mv_bs, mf2, mb2;
extern int print_global_id;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	extern const int external_input[];
	extern const int external_off_AC_2[];
	extern const int external_off_AC_5[];
	extern const int external_off_AC_9[];
	extern const int external_off_AC_12[];
	extern const int external_off_AC_16[];
	extern const int external_off_B[];


	extern const int dut_matrix_L0_0[];
	extern const int mem_off_BASE_AC_EXT[];
	extern const int mem_off_BASE_B_EXT[];
	extern const int dut_matrix_L0_1[];
	extern const int dut_matrix_L0_2[];
	extern const int dut_matrix_L0_3[];
	extern const int dut_matrix_L1_0[];
	extern const int dut_matrix_L1_1[];
	extern const int dut_matrix_L1_2[];
	extern const int dut_matrix_L1_3[];

	extern const int dut_matrix_L2_0[];
	extern const int dut_matrix_L2_1[];
	extern const int dut_matrix_L2_2[];
	extern const int dut_matrix_L2_3[];
	extern const int dut_matrix_L2_4[];
	extern const int dut_matrix_L2_5[];
	extern const int dut_matrix_L2_6[];
	extern const int dut_matrix_L2_7[];
	extern const int dut_matrix_L2_8[];
	extern const int dut_matrix_L2_9[];
	extern const int dut_matrix_L2_10[];
	extern const int dut_matrix_L2_11[];
	extern const int dut_matrix_L2_12[];
	extern const int dut_matrix_L2_13[];
	extern const int dut_matrix_L2_14[];





	extern const int dut_matrix_L3_0[];
	extern const int dut_matrix_L3_1[];
	extern const int dut_matrix_L3_2[];
	extern const int dut_matrix_L3_3[];
	extern const int dut_matrix_L4_0[];
	extern const int dut_matrix_L4_1[];
	extern const int dut_matrix_L4_2[];
	extern const int dut_matrix_L4_3[];
	extern const int dut_matrix_L5_0[];
	extern const int dut_matrix_L5_1[];
	extern const int dut_matrix_L5_2[];
	extern const int dut_matrix_L5_3[];
	extern const int dut_matrix_L5_4[];
	extern const int dut_matrix_L5_5[];

	extern const int dut_matrix_L6_0[];
	extern const int dut_matrix_L6_1[];
	extern const int dut_matrix_L6_2[];
	extern const int dut_matrix_L6_3[];
	extern const int dut_matrix_L7_0[];
	extern const int dut_matrix_L7_1[];
	extern const int dut_matrix_L7_2[];
	extern const int dut_matrix_L7_3[];

	extern const int dut_matrix_L8_0[];
	extern const int dut_matrix_L8_1[];
	extern const int dut_matrix_L8_2[];
	extern const int dut_matrix_L8_3[];
	extern const int dut_matrix_L8_4[];
	extern const int dut_matrix_L8_5[];
	extern const int dut_matrix_L8_6[];
	extern const int dut_matrix_L8_7[];
	extern const int dut_matrix_L8_8[];
	extern const int dut_matrix_L8_9[];
	extern const int dut_matrix_L8_10[];
	extern const int dut_matrix_L8_11[];
	extern const int dut_matrix_L8_12[];
	extern const int dut_matrix_L8_13[];
	extern const int dut_matrix_L8_14[];
	extern const int dut_matrix_L8_15[];
	extern const int dut_matrix_L8_16[];
	extern const int dut_matrix_L8_17[];
	extern const int dut_matrix_L8_18[];
	extern const int dut_matrix_L8_19[];
	extern const int dut_matrix_L8_20[];
	extern const int dut_matrix_L8_21[];
	extern const int dut_matrix_L8_22[];
	extern const int dut_matrix_L8_23[];
	extern const int dut_matrix_L8_24[];
	extern const int dut_matrix_L8_25[];
	extern const int dut_matrix_L8_26[];
	extern const int dut_matrix_L8_27[];
	extern const int dut_matrix_L8_28[];
	extern const int dut_matrix_L8_29[];
	extern const int dut_matrix_L8_30[];
	extern const int dut_matrix_L8_31[];
	extern const int dut_matrix_L8_32[];
	extern const int dut_matrix_L8_33[];
	extern const int dut_matrix_L8_34[];
	extern const int dut_matrix_L8_35[];
	extern const int dut_matrix_L8_36[];
	extern const int dut_matrix_L8_37[];
	extern const int dut_matrix_L8_38[];
	extern const int dut_matrix_L8_39[];
	extern const int dut_matrix_L8_40[];
	extern const int dut_matrix_L8_41[];
	extern const int dut_matrix_L8_42[];
	extern const int dut_matrix_L8_43[];
	extern const int dut_matrix_L8_44[];
	extern const int dut_matrix_L8_45[];
	extern const int dut_matrix_L8_46[];
	extern const int dut_matrix_L8_47[];
	extern const int dut_matrix_L8_48[];
	extern const int dut_matrix_L8_49[];
	extern const int dut_matrix_L8_50[];
	extern const int dut_matrix_L8_51[];
	extern const int dut_matrix_L8_52[];
	extern const int dut_matrix_L8_53[];
	extern const int dut_matrix_L8_54[];
	extern const int dut_matrix_L8_55[];
	extern const int dut_matrix_L8_56[];
	extern const int dut_matrix_L8_57[];
	extern const int dut_matrix_L8_58[];
	extern const int dut_matrix_L8_59[];
	extern const int dut_matrix_L8_60[];
	extern const int dut_matrix_L8_61[];
	extern const int dut_matrix_L8_62[];
	extern const int dut_matrix_L8_63[];




	extern const int dut_matrix_L9_0[];
	extern const int dut_matrix_L9_1[];
	extern const int dut_matrix_L9_2[];
	extern const int dut_matrix_L9_3[];

	extern const int dut_matrix_L9_4[];
	extern const int dut_matrix_L9_5[];

	extern const int dut_matrix_L10_0[];
	extern const int dut_matrix_L10_1[];
	extern const int dut_matrix_L10_2[];
	extern const int dut_matrix_L10_3[];
	extern const int dut_matrix_L11_0[];
	extern const int dut_matrix_L11_1[];
	extern const int dut_matrix_L11_2[];
	extern const int dut_matrix_L11_3[];


extern const int dut_matrix_L12_0[];
extern const int dut_matrix_L12_1[];
extern const int dut_matrix_L12_2[];
extern const int dut_matrix_L12_3[];
extern const int dut_matrix_L12_4[];
extern const int dut_matrix_L12_5[];
extern const int dut_matrix_L12_6[];
extern const int dut_matrix_L12_7[];
extern const int dut_matrix_L12_8[];
extern const int dut_matrix_L12_9[];
extern const int dut_matrix_L12_10[];
extern const int dut_matrix_L12_11[];
extern const int dut_matrix_L12_12[];
extern const int dut_matrix_L12_13[];
extern const int dut_matrix_L12_14[];
extern const int dut_matrix_L12_15[];
extern const int dut_matrix_L12_16[];
extern const int dut_matrix_L12_17[];
extern const int dut_matrix_L12_18[];
extern const int dut_matrix_L12_19[];
extern const int dut_matrix_L12_20[];
extern const int dut_matrix_L12_21[];
extern const int dut_matrix_L12_22[];
extern const int dut_matrix_L12_23[];
extern const int dut_matrix_L12_24[];
extern const int dut_matrix_L12_25[];
extern const int dut_matrix_L12_26[];
extern const int dut_matrix_L12_27[];
extern const int dut_matrix_L12_28[];
extern const int dut_matrix_L12_29[];
extern const int dut_matrix_L12_30[];
extern const int dut_matrix_L12_31[];
extern const int dut_matrix_L12_32[];
extern const int dut_matrix_L12_33[];
extern const int dut_matrix_L12_34[];
extern const int dut_matrix_L12_35[];
extern const int dut_matrix_L12_36[];
extern const int dut_matrix_L12_37[];
extern const int dut_matrix_L12_38[];
extern const int dut_matrix_L12_39[];
extern const int dut_matrix_L12_40[];
extern const int dut_matrix_L12_41[];
extern const int dut_matrix_L12_42[];
extern const int dut_matrix_L12_43[];
extern const int dut_matrix_L12_44[];
extern const int dut_matrix_L12_45[];
extern const int dut_matrix_L12_46[];
extern const int dut_matrix_L12_47[];
extern const int dut_matrix_L12_48[];
extern const int dut_matrix_L12_49[];
extern const int dut_matrix_L12_50[];
extern const int dut_matrix_L12_51[];
extern const int dut_matrix_L12_52[];
extern const int dut_matrix_L12_53[];
extern const int dut_matrix_L12_54[];
extern const int dut_matrix_L12_55[];
extern const int dut_matrix_L12_56[];
extern const int dut_matrix_L12_57[];
extern const int dut_matrix_L12_58[];
extern const int dut_matrix_L12_59[];
extern const int dut_matrix_L12_60[];
extern const int dut_matrix_L12_61[];
extern const int dut_matrix_L12_62[];
extern const int dut_matrix_L12_63[];

//
//
//

 	extern const int dut_matrix_L13_0[];
 	extern const int dut_matrix_L13_1[];
 	extern const int dut_matrix_L13_2[];
// 	extern const int dut_matrix_L13_3[];
 	extern const int dut_matrix_L14_0[];
 	extern const int dut_matrix_L14_1[];
 	extern const int dut_matrix_L14_2[];
// 	extern const int dut_matrix_L14_3[];
// 	extern const int dut_matrix_L15_0[];
//
 extern const int dut_matrix_L15_0[];
 extern const int dut_matrix_L15_1[];
 extern const int dut_matrix_L15_2[];
// extern const int dut_matrix_L15_3[];
// extern const int dut_matrix_L15_4[];
// extern const int dut_matrix_L15_5[];
// extern const int dut_matrix_L15_6[];
// extern const int dut_matrix_L15_7[];
// extern const int dut_matrix_L15_8[];
// extern const int dut_matrix_L15_9[];
// extern const int dut_matrix_L15_10[];
// extern const int dut_matrix_L15_11[];
// extern const int dut_matrix_L15_12[];
// extern const int dut_matrix_L15_13[];
// extern const int dut_matrix_L15_14[];
//
//
extern const int dut_matrix_L16_0[];
extern const int dut_matrix_L16_1[];
extern const int dut_matrix_L16_2[];
extern const int dut_matrix_L16_3[];
extern const int dut_matrix_L16_4[];
extern const int dut_matrix_L16_5[];
extern const int dut_matrix_L16_6[];
extern const int dut_matrix_L16_7[];
extern const int dut_matrix_L16_8[];
extern const int dut_matrix_L16_9[];
extern const int dut_matrix_L16_10[];
extern const int dut_matrix_L16_11[];
extern const int dut_matrix_L16_12[];
extern const int dut_matrix_L16_13[];
extern const int dut_matrix_L16_14[];
extern const int dut_matrix_L16_15[];

		extern const int dut_matrix_L1600_0[];
 	extern const int dut_matrix_L17_0[];
 	extern const int dut_matrix_L17_1[];
 	extern const int dut_matrix_L17_2[];
//
 	extern const int dut_matrix_L18_0[];

//
 	extern const int dut_matrix_L19_0[];
 	extern const int dut_matrix_L20_0[];
 	extern const int dut_matrix_L21_0[];


	// extern const int dut_matrix_L19_1[];
	// extern const int dut_matrix_L19_2[];
	// extern const int dut_matrix_L19_3[];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const int input[3072];
extern const int layer0_bias[];

extern const int layer1_filters[];
extern const int layer1_bias[];
extern const int layer2_filters[];
extern const int layer2_bias[];

extern const int layer4_filters[];
extern const int layer4_bias[];
extern const int layer5_filters[];
extern const int layer5_bias[];

extern const int layer7_filters[];
extern const int layer7_bias[];
extern const int layer8_filters[];
extern const int layer8_bias[];
extern const int layer9_filters[];
extern const int layer9_bias[];

extern const int layer11_filters[];
extern const int layer11_bias[];
extern const int layer12_filters[];
extern const int layer12_bias[];
extern const int layer13_bias[];
extern const int layer13_filters[];

extern const int layer15_filters[];
extern const int layer15_bias[];
extern const int layer16_filters[];
extern const int layer16_bias[];
extern const int layer17_filters[];
extern const int layer17_bias[];

extern const int layer19_filters[];
extern const int layer19_bias[];
extern const int layer20_filters[];
extern const int layer20_bias[];
extern const int layer21_filters[];
extern const int layer21_bias[];

///////////////////////////////////
void convolution2D(int size, int (*matrix)[size], int *kernel, int *out);
//short to_int16(float input,int fraction_size);
int to_int32(float input,int fraction_size);
/*
 * Function that receives a pointer to a square matrix of size 'size'
 * and analyzes each element: if an element is less than 0, then it
 * forces it to 0; otherwise it returns that element as it is.
 */
void relu(int size, int *input);

/*
 * Function that receives a pointer to a vector of length 'size'
 * and analyzes each element: if an element is less than 0, then it
 * forces it to 0; otherwise it returns that element as it is.
 */
void reluVect(int size, int *input);

/*
 * Function that receives a pointer to an 'input' square matrix of size 'size_i'
 * and returns a square matrix of size 'size_o' (possibly a vector) whose elements are the maximum element
 * of each submatrix of size 'size_o' within 'input' (stride = 2, pad = 2).
 */
void maxpool(int size_i, int *input, int size_o, int *output);

/*
 * Function that returns the product between two vectors 'a' and 'b' of length 'dim'.
 */
int fullyconnect(int dim, int *a, int *b);

/*
 * Function that receives a pointer to a vector 'vect' and returns a vector 'softmax' whose
 * elements are a normalization of the original ones. 'dim' is the vector length.
 */
void softmax (int dim, int *input, float *output);

/*
 * Function that takes two square matrixes of size 'size' as input
 * and puts into 'dest' the sum of 'dest' itself and 'source.
 */
void cumulativeSum(int size, float *dest, float *source);

/*
 * Function that reads the file pointed by 'fp', and put 'num_param' parameters into 'kernel' starting from the 'i'-th row
 * and the 'k'-th row. The inputs 'maxColumn' and 'maxRow' are respectively the number of parameters in the current filter,
 * and the numer of filters in the current layer.
 * es: in conv2 there are 64 filters (maxRow=63) and each filter has 3x3x64=576 (maxColumn= 575) parameters.
*/


//void getWeights(FILE *fp, int num_param, int i, int k, int maxColumn, int maxRow, float *Kernel);
void getWeights(const int *fp, int num_param, int *kernel, int cont);


/*
 * Function that initialize each element of a matrix 'matrix' of size 'size' to 0.
 */
void matrixReset(int size, int *matrix);

/*
 * Function that receives a pointer to a matrix of size 'size' and
 * adds a bias to each element belonging to that matrix.
 */
void addBias(int size, int *matrix, int bias);

/*
 * Function that reads the file pointed by 'fp' and returns a floating number
 * to be used later as a bias.
 */
int getBias(const int *ptb,int cont);

/*
 * Function that reads the file containing the classes recognized by the network
 * and, receiving an integer representing the position of the result in the softmax vector,
 * displays on screen the name of the class recognized.
 */
void displayResult(FILE *fp, int pos);

//functions for debugging
// void printmod_sel(int layer,int ch, int dim_i, int dim_j, int *input,int shift);
// void printmod_full(int layer,int ch, int dim_i, int dim_j, int *input, int shift);
// void dbg_count_zero(int ch, int dim_i, int dim_j,int *input);
// void spegni_threads();
void display_spm_matrix(int size_r,int size_c,void* pt_spm_mat);
// void display_spm_matrix_scal(int ch, int size_r,int size_c,void* pt_spm_mat, int shift);
// void isequal(int row, int col, int *pt1, int *pt2);

// funzioni aggiornate per spm+DSP
void getFeatures_SPM(void* spm_dest, int size, int (*pt_to_fm)[size]);
void getFeatures_SPM_fully(void* spm_dest, int size, int *pt_to_fm);
void getWeights_SPM	(void *spm_dest, const int *pt_to_wh, int num_param, int offset);
void convolution2D_SPM(void* spm_dest, void* spm_fm, void* spm_krn, int mat_size);
void getBias_SPM		(void *spm_dest, const int *pt_to_bs,	int offset);
void getBias_SPM_fully(void *spm_dest, const int *pt_to_bs,int offset, int size);
void addBias_SPM		(void *spm_dest, void *spm_src,	void *spm_bias, int size);
void relu_SPM(void *spm_dest, void *spm_src, int size, int *mem_dest);
void relu_SPM_fully(void *spm_dest, void *spm_src, int size, int *mem_dest);

void fullyconnect_SPM(void *spm_dest, void *spm_src1, void *spm_src2,int dim);
