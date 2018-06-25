//////////////////////////////////////////////
//	Struction.h								//
//	2013/3/28								//
//	擷取某點某個範圍顏色時所用的結構		//
//////////////////////////////////////////////
#ifndef RGB_Range_STRUCTION
#define RGB_Range_STRUCTION

struct RGB_Range{
	int B_lower_limit;
	int B_upper_limit;
	int G_lower_limit;
	int G_upper_limit;
	int R_lower_limit;
	int R_upper_limit;
};

struct RGB_Struction{
	int B;
	int G;
	int R;
};

#endif