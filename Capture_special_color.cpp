////////////////////////////////
//purpose:�qOriginal����S�w�d���C��A�öK��Buffer�۹�������m�W
//return:�Ϥ����Q����������Ӽ�
////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

#define RGB 3

int Capture_special_color( IplImage* Original, IplImage* Buffer, RGB_Range* color_limit){

	int i, j;
	int Capture_point_number = 0;

	for( i = 0; i <  Original->height; i++ ){
		for( j = 0; j < Original->width; j++ ){
			if(    ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ] >= color_limit->B_lower_limit )		/*Blue_lower_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ] <= color_limit->B_upper_limit )		/*Blue_upper_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1] >= color_limit->G_lower_limit )	/*Green_lower_limit*/  
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1 ] <= color_limit->G_upper_limit )	/*Green_upper_limit*/ 
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ] >= color_limit->R_lower_limit )	/*Red_lower_limit*/
				&& ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ] <= color_limit->R_upper_limit )	/*Red_upper_limit*/ )
			{
				//Blue
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels) ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ];
				//Green
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels)+1 ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels)+1 ];
				//Red
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels)+2 ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels)+2 ];
				//Capture_point_number�`�ƭp��
				Capture_point_number++;
			}
		}
	}

	return Capture_point_number;
}