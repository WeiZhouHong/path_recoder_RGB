////////////////////////////////
//purpose:從Original除去特定的顏色，並將特定的顏色之外的部分貼到Buffer相對應的位置上
////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

#define RGB 3

void Remove_special_color( IplImage* Original, IplImage* Buffer, int R, int G, int B){

	int i, j;

	for( i = 0; i <  Original->height; i++ ){
		for( j = 0; j < Original->width; j++ ){
			if(    ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ] != B )/*Blue*/ 
				|| ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +1 ] != G )/*Green*/ 
				|| ( (unsigned char)Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) +2 ] != R)/*Red*/ )
			{
				//Blue
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels) ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels) ];
				//Green
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels)+1 ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels)+1 ];
				//Red
				Buffer->imageData[ i*(Buffer->widthStep) + j*(Buffer->nChannels)+2 ] = Original->imageData[ i*(Original->widthStep) + j*(Original->nChannels)+2 ];
			}
		}
	}
}