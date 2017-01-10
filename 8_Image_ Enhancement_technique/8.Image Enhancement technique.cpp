#include "opencv2\opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
//By Shridhar Kini(Subscribe to: OpenCVstyle in YouTube)
char* inImagePath;
int option=1;
float c;
void trackBarMoved(int pos,void *y)
{
	Mat image = imread(inImagePath,0);
	image.convertTo(image,CV_32F);//converting from CV_8U to CV_32F
	image=image*(.003921);//dividing by 255 to make it floating point

/*	for(int i=0;i<image.rows;i++){ //this loop is to confirms data are now converted to 0 to 1
		if(i>3) break;				//so that we can do any power options
		for(int j=0;j<image.cols;j++)
		{
			if(j<3)
			cout<<image.at<float>(i,j)<<" ";
		}
		cout<<endl;
	}*/
	
	if(option == 1)//do log transform
	{
		image = image + 1;//taking log to (0,1) yields -ve value
		log(image,image);//at max the result will lie between 0 to .6931
		//now we need to map 0 to .69314 to 0 to 1
		double minVal,maxVal;
		minMaxLoc(image,&minVal,&maxVal);
		cout<<"min="<<minVal<<" max="<<maxVal<<endl;
		Mat fs;
		fs = image - (float)minVal;
		image = 255*(fs/(float)maxVal);
	}
	else if(option == 2) // do gamma transform
	{
		float x;
		if(pos == 10)//convert trackBar position to appropiate value
		{
			x=1.0;
		}
		else if(pos < 10)
		{
			x=(float)pos*.1;
		}
		else
		{
			x = (pos-10)*.5 + 1;
		}
		pow(image,x,image);
		image = image*c;
		image = image*255;
		cout<<"y(gamma) ="<<x<<endl;
	}
	else
	{
		image = 1.0-image;
		image = image*255;
	}
	
	image.convertTo(image,CV_8U);
	imshow("Output",image);
}

int main(int argc, char ** argv)
{
	Mat inImage;	
	inImagePath = "G:/OpenCVProjects/opencv/samples/cpp/baboon.jpg";
	inImage = imread(inImagePath,0);
	if(!inImage.data )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
	namedWindow("Input Image",CV_WINDOW_AUTOSIZE);
	imshow("Input Image",inImage);

	int trackBarPosition=10;
	namedWindow("Output",CV_WINDOW_AUTOSIZE);
	imshow("Output",inImage);
	cout<<"imgae details are"<<endl;
	cout<<inImage.rows<<"x"<<inImage.cols<<" "<<inImage.type()<<endl;
	inImage.release();//destroy the inImage as it is not required any more
	
	//register the trackbar
	createTrackbar("trackbar1","Output",&trackBarPosition,20,trackBarMoved,NULL);//20 is for max value of trackbar
	
		cout<<"LOG OR POWERTRANSFORM OR NEGATIVE(1 or 2 or 3 or any other to quit)"<<endl;
		cin>>option;
		if(option == 1)
		{
			cout<<"S = x*LOG(1+R),R is input image,x = 1"<<endl;//for log  transform
		}
		else if(option == 2)
		{
			cout<<"S = C*R^y,R is input image,y is choosen from slider, give the C value"<<endl;//for power or gamma transform
			cout<<"C = ?";
			cin>>c;
		}
		else if(option == 3)
		{
			cout<<"Negative of the Image"<<endl;
		}
		else
		{
			exit(0);
		}

	waitKey(0);
	return 0;
}
