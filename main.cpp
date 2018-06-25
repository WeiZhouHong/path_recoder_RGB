#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h> 
#include "Struction.h"

#define RGB 3

int Avi_To_Jpg();
void Mask_Filter(IplImage* Temp, IplImage* Path, RGB_Range* Red_Path);
int Capture_special_color( IplImage* Original, IplImage* Buffer, RGB_Range* color_limit);
void Remove_special_color( IplImage* Original, IplImage* Buffer, int R, int G, int B);
int Grab_Center(IplImage* Original, RGB_Range* color_limit);

//struct RGB_Range Red_Path = {0,50,0,50,100,255};   //{B的底限,B的上限,G的底限,G的上限,R的底限,R的上限}
//struct RGB_Range Green_Path = {0,150,100,255,0,50};  ////{B的底限,B的上限,G的底限,G的上限,R的底限,R的上限}

struct RGB_Range Red_Path	= {0,50,0,50,100,255};   //{B的底限,B的上限,G的底限,G的上限,R的底限,R的上限}
struct RGB_Range Green_Path = {100,255,100,255,100,255};  //{B的底限,B的上限,G的底限,G的上限,R的底限,R的上限}

int main()
{

	int i = 0, j = 0, k = 0;	//Count
	int Total_Num = 0;			//圖片編號
	int Red_Center;	//截圖的紅點平均位置
	int Green_Center;	//截圖的綠點平均位置
	int Robot_Center_X,Robot_Center_Y;
	int Vertical_Distance,Horizontal_Distance;	//機器人中心離四個角的距離
	char Original_Picture_Num[20];	//原始截圖的名稱
	char Filtered_Picture_Num[20];	//過濾後截圖的名稱

	//分配圖片記憶體位置
	IplImage* Path = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
	IplImage* Body = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
	IplImage* Map = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
	IplImage* Temp = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
	IplImage* Frame = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);

	//讀取圖片
	Path = cvLoadImage("Blank.jpg");
	Body = cvLoadImage("Blank.jpg");
	Map = cvLoadImage("Map.jpg");
	Temp = cvLoadImage("Blank.jpg");
	Frame = cvLoadImage("Map.jpg");

	//檢查是否讀取成功
	if( !Path || !Temp || !Body || !Map || !Frame){
		printf("Could not load image file\n");
		system("pause");
		return 0;
	}

	//將影片轉換成Jpg截圖
	Avi_To_Jpg();

	while( Temp ){		
		//以遮罩過濾圖片Temp紅色的點並存到圖片Path
		Mask_Filter(Temp, Path, &Red_Path);
		//以遮罩過濾圖片Temp紅色的點並存到圖片Path
		Mask_Filter(Temp, Path, &Green_Path);
		//抓取圖片色塊的中心點
		Red_Center = Grab_Center(Path, &Red_Path);
		Green_Center = Grab_Center(Path, &Green_Path);
	/*產生中心點及機器人外框*/
	if( Red_Center != -1 && Green_Center != -1 ){
		Robot_Center_X = Red_Center%Path->width;
		Robot_Center_Y = Red_Center/Path->width;
		cvCircle( Body, cvPoint(Robot_Center_X, Robot_Center_Y), 1, cvScalar(255,255,0), 1);

		Vertical_Distance = (Robot_Center_Y)-(Green_Center/Path->width);
		Horizontal_Distance = (Robot_Center_X)-(Green_Center%Path->width);

//		cvRectangle( Body, cvPoint(Green_Center%Path->width, Green_Center/Path->width), cvPoint(2*(Red_Center%Path->width)-(Green_Center%Path->width), 2*(Red_Center/Path->width)-(Green_Center/Path->width)), cvScalar(255,255,255), 1 );
		cvLine(Body, cvPoint(Robot_Center_X-Horizontal_Distance,Robot_Center_Y-Vertical_Distance), cvPoint(Robot_Center_X+Vertical_Distance,Robot_Center_Y-Horizontal_Distance), cvScalar(0,255,0), 1);
		cvLine(Body, cvPoint(Robot_Center_X+Vertical_Distance,Robot_Center_Y-Horizontal_Distance), cvPoint(Robot_Center_X+Horizontal_Distance,Robot_Center_Y+Vertical_Distance), cvScalar(0,255,0), 1);
		cvLine(Body, cvPoint(Robot_Center_X+Horizontal_Distance,Robot_Center_Y+Vertical_Distance), cvPoint(Robot_Center_X-Vertical_Distance,Robot_Center_Y+Horizontal_Distance), cvScalar(0,255,0), 1);
		cvLine(Body, cvPoint(Robot_Center_X-Vertical_Distance,Robot_Center_Y+Horizontal_Distance), cvPoint(Robot_Center_X-Horizontal_Distance,Robot_Center_Y-Vertical_Distance), cvScalar(0,255,0), 1);
		//中心點重置
		Red_Center = -1; Green_Center = -1;
	}
	/*個別截圖用*/
		//機器人本體
		Remove_special_color( Body, Frame, 231, 35, 231);
		//機器人路徑
		Remove_special_color( Path, Frame, 231, 35, 231);
	/*路徑紀錄用*/
		//機器人本體
		Remove_special_color( Body, Map, 231, 35, 231);
		//機器人路徑
		Remove_special_color( Path, Map, 231, 35, 231);
/////////////////////////////////////////////
		//圖片編號改變
		Total_Num++;
		//讀取影片截圖
		cvReleaseImage(&Temp);
//		IplImage* Temp = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
		sprintf( Original_Picture_Num, "Original%d.jpg", Total_Num );
		Temp = cvLoadImage( Original_Picture_Num );
		//儲存過濾後的截圖
		sprintf( Filtered_Picture_Num, "Filtered%d.jpg", Total_Num );
		cvSaveImage( Filtered_Picture_Num,Frame );
		//重置個別截圖用的記憶圖

		cvReleaseImage(&Frame);
		cvReleaseImage(&Path);


//		IplImage* Frame = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);
//		IplImage* Path = cvCreateImage( cvSize(800,640), IPL_DEPTH_32F, RGB);


		Frame = cvLoadImage("Blank.jpg");
		Path = cvLoadImage("Blank.jpg");

	}
/////////////////////////////////////////////
	//視窗顯示
//	cvNamedWindow("win1", CV_WINDOW_AUTOSIZE);	//創造視窗顯示
//	cvShowImage("win1",Map);	//將顯示圖於視窗顯示
//    cvWaitKey(0);	//視窗內任意鍵結束

	if(!cvSaveImage("Robot_Path.jpg",Map)){ 
		printf("Could not save: %s\n", "Robot_Path.jpg" );
		system("pause");
	}
	//釋放圖片記憶體
//	cvReleaseImage(&Path);
	cvReleaseImage(&Body);
	cvReleaseImage(&Map);
	cvReleaseImage(&Temp);
//	cvReleaseImage(&Frame);

    return 0;
}



