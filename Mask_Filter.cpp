#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

#define Mask_size 3			//�H3x3���B�n�j�p�z��

void Mask_Filter(IplImage* Temp, IplImage* Path, RGB_Range* Red_Path){
	int i,j,k,l;

	for( i = 0; i <  (Temp->height)-Mask_size; i=i+1 ){
		for( j = 0; j < (Temp->width)-Mask_size; j=j+1 ){
			//�ˬd Mask �����X�I�ŦX���w�C��d�򪺭p�ƾ�
			int Mask_Check = 0;				
			for( k = 0; k < Mask_size; k++ ){
				for( l = 0; l < Mask_size; l++ ){			
					//�ˬd�I�O�_�ŦX�C��d��
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
			//�Y Mask �ŦX����h�N Mask �z�諸�I�л\�L�h
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
/*				//Averger_Red_point�`�M
				Averger_Red_point = Averger_Red_point + (i*(Temp->widthStep) + j*(Temp->nChannels));
				//�p��Averger_Red_point������
				k++;*/
