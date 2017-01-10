#include "opencv2\opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void myhist(Mat &med,Mat &asd)
{
	asd.setTo(0);//initialize asd to zero
	float maxi=0;//used in drawing the histogram(required while drawing) 
	//med.convertTo(med,CV_32FC1);//converted it float for easing the access

	float *y = asd.ptr<float>(0);//y points to row of asd
	for(int i=0;i<med.rows;i++)//run throught the rows
	{	
		uchar *x = med.ptr<uchar>(i);//x points to row of med
		for(int j=0;j<med.cols;j++)//run throught the cols
		{
			for(int k=0;k<256;k++)//255 intrensities
			{
				if(k==(int)x[j])//check if med.at(k) is equal to kth intensity level
				{
					y[k] +=1;//if true increment the count at kth position in asd
					if(maxi < y[k])//to calculate maximum in the array(it is calculated only when array value is upadated)
					{
						maxi = y[k];
					}
					break;
				}
			}
		}
	}
	y[256]=maxi;//maximum will be stored in the max in 257th location of array
}
void drawHist(Mat &asd,char *winName)
{
	
	Mat histFig(640,512,CV_8U);//256*2 = 512,so thickness of line drawn will be 2
	histFig.setTo(255);//white background image 
	namedWindow(winName);
	

	//to print maximum available in asd
	cout<<"max in asd[256] for"<<asd.at<float>(256)<<endl;

	float *y = asd.ptr<float>(0);//y points to row of asd
	float max=y[256];//get the max value present in asd(256)
	float factor = ((float)640/max);//amounts to 1 pixel height
	
	for(int i=0;i<256;i++)
	{
		y[i] *= factor;
		Point pt1,pt2;
		pt1 = Point(2*i,640);
		pt2 = Point(2*i,640-(int)y[i]);
		const Scalar col = Scalar(0,0,0);
		line(histFig,pt1,pt2,col,2,CV_AA);
	}
	imshow(winName,histFig);
}
int main(int argc, char **argv)
{
	Mat image1;	
	if( argc <2)
    {
     cout <<" less arguments" << endl;
     return -1;
    }
	image1 = imread(argv[1],0);//0 for grayscale
	if(!image1.data )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
	namedWindow("Input",CV_WINDOW_AUTOSIZE);
	imshow("Input",image1);

	Mat asd(1,257,CV_32F);//element at 257 is the maximum element
	myhist(image1,asd);//calulates the histogram
	
	drawHist(asd,"Without Blurred");//draws the histogram

	Mat blurred;
	medianBlur(image1,blurred,5);
	namedWindow("BluredInput",1);
	imshow("BluredInput",blurred);
	myhist(blurred,asd);//calulates the histogram
	
	drawHist(asd,"With Blurred");//draws the histogram*/

	waitKey(0);
	return 0;
}