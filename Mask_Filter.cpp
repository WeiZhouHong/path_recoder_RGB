#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

#define Mask_size 3			//以3x3的遮罩大小篩選

void Mask_Filter(IplImage* Temp, IplImage* Path, RGB_Range* Red_Path){
	int i,j,k,l;

	for( i = 0; i <  (Temp->height)-Mask_size; i=i+1 ){
		for( j = 0; j < (Temp->width)-Mask_size; j=j+1 ){
			//檢查 Mask 內有幾點符合指定顏色範圍的計數器
			int Mask_Check = 0;				
			for( k = 0; k < Mask_size; k++ ){
				for( l = 0; l < Mask_size; l++ ){			
					//檢查點是否符合顏色範圍
					if(  ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) ] >= Red_Path->B_lower_limit )		/*Blue_lower_limit*/ 
						&& ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) ] <= Red_Path->B_upper_limit )		/*Blue_upper_limit*/ 
						&& ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +1 ] >= Red_Path->G_lower_limit )	/*Green_lower_limit*/  
						&& ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +1 ] <= Red_Path->G_upper_limit )	/*Green_upper_limit*/ 
						&& ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +2 ] >= Red_Path->R_lower_limit )	/*Red_lower_limit*/
						&& ( (unsigned char)Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +2 ] <= Red_Path->R_upper_limit )	/*Red_upper_limit*/ )
					{
						Mask_Check++;
					}
				}
			}
			//若 Mask 符合條件則將 Mask 篩選的點覆蓋過去
			if( Mask_Check >= (Mask_size*Mask_size) ){
				for( k = 0; k < Mask_size; k++ ){
					for( l = 0; l < Mask_size; l++ ){	
						//Blue
						Path->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) ] = Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) ];
						//Green
						Path->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +1 ] = Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +1 ];
						//Red
						Path->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +2 ] = Temp->imageData[ i*(Temp->widthStep) + j*(Temp->nChannels) + k*(Temp->widthStep) + l*(Temp->nChannels) +2 ];
					}
				}
			}
		}
	}
}
/*				//Averger_Red_point總和
				Averger_Red_point = Averger_Red_point + (i*(Temp->widthStep) + j*(Temp->nChannels));
				//計算Averger_Red_point的除數
				k++;*/
