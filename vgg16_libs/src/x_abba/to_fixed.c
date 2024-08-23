#include"Definitions_fully_test.h"

short to_int16(float input,int fraction_size)
{
	return (short)round((input*pow(2,fraction_size)));
};

int to_int32(float input,int fraction_size)
{
	return (int)round((input*pow(2,fraction_size)));
};