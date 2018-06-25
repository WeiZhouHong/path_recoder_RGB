#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 

int Avi_To_Jpg()
{
	//Count
	int i;
	int Total_Num = 0;
	char Video_Num[20];
	//���t�v���O�����m
	CvCapture* capture;
	//Ū���v��
	capture = cvCaptureFromAVI("Path.avi");
	//�ˬd�O�_Ū�����\
	if( !capture ){
		printf("Could not load image file: %s\n","test.jpg");
		system("pause");
		return 0;
	}
	cvQueryFrame(capture); // �bŪ�����W�y�H���e�A�n�����榹�ާ@

	IplImage* img = 0; 
	int nFrames = 400;	//�^���Ϥ��i��
	for(i=0;i<nFrames;i++){
		cvGrabFrame(capture);          // capture a frame
		img=cvRetrieveFrame(capture);  // retrieve the captured frame
		Total_Num++;
		sprintf( Video_Num, "Original%d.jpg", Total_Num );
		if(!cvSaveImage( Video_Num, img)){
			printf("Could not save: %s\n", Video_Num);
			break;
		}
		cvShowImage("mainWin", img); 
		cvWaitKey(20); 
	}

    return 0;
}



