#include <iostream>
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;
//By Shridhar Kini(Subscribe to: OpenCVstyle in YouTube)
int main( int argc, char** argv )
{
    if( argc < 2)
    {
    	cout <<" less number of arguments" << endl;
    	return -1;
    }
	//char* path = "G:\OpenCVProjects\opencv\samples\cpp\baboon.jpg";
	//char* path = "G:/OpenCVProjects/opencv/samples/cpp/baboon.jpg";
	//Mat image = imread(path,1);
	Mat image = imread(argv[1],1);
	if(!image.data)
	{
		cout<<"could not load image"<<endl;
		return -1;
	}
	namedWindow("Image",CV_WINDOW_NORMAL|CV_WINDOW_KEEPRATIO);
	imshow("Image",image);

	waitKey(0);
	return 0;
}
