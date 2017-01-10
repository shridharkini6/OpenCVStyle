#include "opencv2\opencv.hpp"
#include <iostream>
#include <list>

using namespace std;
using namespace cv;

/*
	176<= Red <=180 
	63 <= Green <= 72
	93 <= skyBlue <= 99
	165 <= Pink <= 171
	36 <= lightGreen <= 39
	9 <= Brown <= 13
*/
void getBlackAndWhiteImageOfObject(Mat &rgbCol,Mat &black)  //retruns half sized b&w image of particular object
{
	//splitting the hsv planes and displaying conntent of each planes
	Mat hsv;
	cvtColor(rgbCol,hsv,CV_BGR2HSV);//7th video lecture

	Mat smallHSV;
	resize(hsv,smallHSV,Size((hsv.cols)/2,(hsv.rows)/2));
	hsv.release();

	vector<Mat> planes;//5th video lecture
	split(smallHSV,planes);	//planes will have h,s,v matrix

	black.create(smallHSV.rows,smallHSV.cols,CV_8U);// black holds image with only specific coloured object
	black.setTo((uchar)0);
	//this loop calulates a presence of particular hue object in the image
	for(int i=0;i<smallHSV.rows;i++)
	{
		uchar* x = planes[0].ptr<uchar>(i);
		for(int j=0;j<smallHSV.cols;j++)
		{
			int t=(int)x[j];
			if(t >= 165 && t<= 171){ //h>174 coorresponds to red colored object
				black.at<uchar>(i,j) = (uchar)255;
			}
		}
	}
	
}

void removeDisjointSetFromBlackAndWhiteImage(Mat &black)
{
	//we need to use 2 pass method for connected component test
	Mat blackCopy(black.rows,black.cols,CV_32FC1);  //this will contain the final connected component colored object
	blackCopy.setTo(0);

	//first pass
	float setNumber=1;  //keeps the set Number( for each set in one row setNumber increments,so each set in a row gets different number)
	for(int i=0;i<black.rows;i++)
	{
		uchar* x = black.ptr<uchar>(i);   // used for accessing
		float* y = blackCopy.ptr<float>(i);    // used for setting
		for(int j=0;j<black.cols;j++)
		{
			if((int)x[j] == 255 )      //x[j] is 255 for particular hue value that you have choosen
			{ 
				if((j==0) || (y[j-1] == setNumber))  //if (y[j-1] == setNumber) is 1, refers jth and (j-1) elements are neibhour else not neighbour
				{
					y[j] = setNumber;
				}
				else
				{
					setNumber++;
					y[j] = setNumber;
				}
			}
		}
	}


	//second pass
	Mat a(1,100,CV_32FC1);    //a holds the number of pixels of same number
						//as we are interested in max number of pixel number, we can avoid identifying less numbered pixel number 
	a.setTo(0);
	float* aRow = a.ptr<float>(0);
	for(int row=1; row<blackCopy.rows; row++)
	{
		float* x = blackCopy.ptr<float>(row);//present row
		for(int col = 0; col<blackCopy.cols; col++)
		{
			if(x[col] != 0)//checking for nonzero content in rows
			{
					float* y = blackCopy.ptr<float>(row-1);//y point to previous row of x
					if(col != 0)//column should not be zeroth column
					{
						if(y[col] != 0)
						{
							float t = y[col];
							x[col] = t;
							aRow[(int)t]++;
						}
						else if(y[col - 1] != 0)
						{
							float t = y[col-1];
							x[col] = t;
							aRow[(int)t]++;
						}
						else if(x[col - 1] != 0)
						{
							float t = x[col-1];
							x[col] = t;
							aRow[(int)t]++;
						}
						else {}
					}
					else
					{
						if(y[col] != 0)
						{
							float t = y[col];
							x[col] = t;
							aRow[(int)t]++;
						}
					}
			}
		}
		cout<<endl;
	}
	int max=0;     //max variable holds max number of connected component
	int maxI=0;		//maxI variable holds max pixel number of connected component
	for(int i=0;i<a.cols;i++)  // printing pixel number and its number of occurence
	{
		if(aRow[i] != 0)
		{
			cout<<"i="<<i<<" a[i]="<<aRow[i]<<endl;
			if(aRow[i]>max)
			{
				max=aRow[i];
				maxI=i;
			}
		}
	}
	cout<<"maxI="<<maxI<<" max="<<max;

	//now change the black variable content
	//replace every other pixel to 0 except maxI.replace maxI to 255
	for(int row=0; row<black.rows; row++)
	{
		uchar* x = black.ptr<uchar>(row);
		float* y = blackCopy.ptr<float>(row);
		for(int col = 0; col<black.cols; col++)
		{
			if((int)y[col] == maxI)
			{
				x[col] = (uchar)255;
			}
			else
			{
				x[col] = 0;
			}
		}
	}

}


void getContourImageOfObject(Mat &rgbCol,Mat &contour)  // retrurns the counter of particular object.size is same as original rgb image
{
	Mat black;
	getBlackAndWhiteImageOfObject(rgbCol,black);
	/*namedWindow("me");
	imshow("me",black);*/


	//try to get the small size of particular object using erosion
	Mat blackEroded;
	Mat structElement = Mat::ones(5,5,CV_8UC1);
	erode(black,blackEroded,structElement,Point(-1,-1),1);
	dilate(blackEroded,blackEroded,structElement,Point(-1,-1),1);//now blackEroded matrix will not have stray white pixel
	blackEroded.copyTo(black);    //update black matrix with unwanted white pixel removed from old black matrix
	
	//a connected component analysis removes all disjoint sets except the color that is intedded
	//removeDisjointSetFromBlackAndWhiteImage(black);
	//black.copyTo(blackEroded);

	structElement = Mat::ones(3,3,CV_8UC1);
	erode(blackEroded,blackEroded,structElement,Point(-1,-1),2);
	structElement.release();
	/*namedWindow("me3");
	imshow("me3",blackEroded)*/;
	
	//try to get contour of the object
	Mat finalBlack;
	subtract(black,blackEroded,finalBlack);  //get boundary by sudbtraction with eroded image
	black.release();
	blackEroded.release();
	//namedWindow("me3");
	//imshow("me3",finalBlack);


	//resize the contour to fit the original object
	resize(finalBlack,contour,Size(),2,2,CV_INTER_CUBIC);
	/*namedWindow("me4");
	imshow("me4",contour);*/

}


void addContourToOriginalImage(Mat& rgbCol,Mat& contour,Mat& final)
{
	//to access r,g,b content to make black backgound around object
	vector<Mat> rgbPlanes;//this will constitute b,g,r planes
	split(rgbCol,rgbPlanes);

	//create contour to be black in original RGB image		
	for(int i=0;i<rgbCol.rows;i++)
	{
		uchar* y = contour.ptr<uchar>(i);    //y will have access to i th row of contour matrix
		for(int j=0;j<rgbCol.cols;j++)
		{
			int t=(int)y[j];    //get (i,j)th element in t of contour matrix
			
			//int f=(int)x[j];       //f holds hue of individual pixel
			if(t>250 )      //to check presence of white marker in contour Matrix and color same we wished to find out
			{
				uchar* x = rgbPlanes[0].ptr<uchar>(i); // x now points b plane	
				x[j] = 0;
				x = rgbPlanes[1].ptr<uchar>(i);     // x now points g plane
				x[j] = 0;
				x = rgbPlanes[2].ptr<uchar>(i);     // x now points r plane
				x[j] = 0;
			}
		}
	}
	merge(rgbPlanes,final);//merging r,g,b planes
}

int main(int argc,char** argv)
{
	if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat rgbCol = imread(argv[1],1);
	if(!rgbCol.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",rgbCol);
	
	Mat contour;
	getContourImageOfObject(rgbCol,contour);
	/*namedWindow("me4");
	imshow("me4",contour);*/

	Mat final;
	addContourToOriginalImage(rgbCol,contour,final);

	namedWindow("me5");
	imshow("me5",final);

	waitKey(0);
	return 0;
}

