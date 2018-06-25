#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

int Grab_Center(IplImage* Original, RGB_Range* color_limit){
	int i, j;
	int x=0, y=0, point_numbers=0;
//	const int height = 272;
//	const int width = 480;
//	struct RGB_Struction TwoD_Register[height][width];

/*	for(i=0; i<height; i++){
		for(j=0; j<width; j++){
			TwoD_Register[i][j].B = (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ];
			TwoD_Register[i][j].G = (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1 ];
			TwoD_Register[i][j].R = (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ];
		}
	}*/
	for(i=0; i<Original->height; i++){
		for(j=0; j<Original->width; j++){
			if(    ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ] >= color_limit->B_lower_limit )		/*Blue_lower_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ] <= color_limit->B_upper_limit )		/*Blue_upper_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1] >= color_limit->G_lower_limit )	/*Green_lower_limit*/  
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1 ] <= color_limit->G_upper_limit )	/*Green_upper_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ] >= color_limit->R_lower_limit )	/*Red_lower_limit*/
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ] <= color_limit->R_upper_limit )	/*Red_upper_limit*/ )
			{
				x = x + i;
				y = y + j;
				point_numbers = point_numbers + 1;
			}
		}
	}

	if( point_numbers > 0)
		return (x/point_numbers)*Original->width + y/point_numbers;
	else
		return -1;
}