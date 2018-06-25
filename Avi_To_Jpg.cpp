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
	//分配影片記憶體位置
	CvCapture* capture;
	//讀取影片
	capture = cvCaptureFromAVI("Path.avi");
	//檢查是否讀取成功
	if( !capture ){
		printf("Could not load image file: %s\n","test.jpg");
		system("pause");
		return 0;
	}
	cvQueryFrame(capture); // 在讀取視頻流信息前，要先執行此操作

	IplImage* img = 0; 
	int nFrames = 400;	//擷取圖片張數
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



