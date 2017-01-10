#include "opencv2\opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
//By Shridhar Kini(Subscribe to: OpenCVstyle in YouTube)
int main(int argc, char** argv)
{
	//for grayscale(1D) pixel access in Mat
	if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat grayImg = imread(argv[1],0);//0 for grayscale image reading
	if(!grayImg.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",grayImg);

	for(int i=0;i< grayImg.rows;i++)	    //run throught the rows
	{
		if(i<20)
		{
			for(int j=0;j< grayImg.cols;j++)//run throught the cols
			{
				if(j<20)
				{
					cout<<(int)grayImg.at<uchar>(i,j)<<" ";    //for getting 
					grayImg.at<uchar>(i,j) = 0;					//for setting
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	namedWindow("Final");
	imshow("Final",grayImg);
	
//---------------------------------------------------------------------------------------------------
	
	//for grayscale(1D) pixel access in Mat
	/*if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat grayImg = imread(argv[1],0);//0 for grayscale image reading
	if(!grayImg.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",grayImg);
	
	
	for(int i=0;i< grayImg.rows;i++)	    //run throught the rows
	{
		if(i<20)
		{
			for(int j=0;j< grayImg.cols;j++)//run throught the cols
			{
				if(j<20)
				{
					cout<<(int)*(grayImg.data+grayImg.step[0]*i+grayImg.step[1]*j)<<endl;	//for getting
	//here grayImg.data+grayImg.step[0]*i+grayImg.step[1]*j calulates address of pixel at (i,j)
	// so by making use of dereferncing operator * you can access (i,j)th element
					*(grayImg.data+grayImg.step[0]*i+grayImg.step[1]*j) = 0;     //for setting
					
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	namedWindow("Final");
	imshow("Final",grayImg);
	*/
//-------------------------------------------------------------------------------------------------------	
	//for grayscale(1D) pixel access in Mat
	/*if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat grayImg = imread(argv[1],0);//0 for grayscale image reading
	if(!grayImg.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",grayImg);

	for(int i=0;i< grayImg.rows;i++)	    //run throught the rows
	{
		if(i<20)
		{
			uchar *rowPtr = grayImg.ptr<uchar>(i);//rowPtr holds the pointer to ith row
				//so changes to rowPtr intern changes the grayImg
			for(int j=0;j< grayImg.cols;j++)//run throught the cols
			{
				if(j<20)
				{
					cout<<(int)rowPtr[j]<<" ";  //for getting
					rowPtr[j]=0;    //for setting
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	namedWindow("Final");
	imshow("Final",grayImg);*/
//---------------------------------------------------------------------------------------------------
/*Resolution of the Image
		Width = 819 pixels
		Height = 460 pixels
	*/
	
	/*if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat Img = imread(argv[1],1);//1 for color image reading
	if(!Img.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	for(int i=0;i<Img.step[1];i++)
	{
		for(int j=0;j<Img.rows;j++)
		{
			if(j<20)
			{
				for(int k=0;k<Img.cols;k++)
				{
					if(k<20)
					{
						cout<<(int)*(Img.data + i + Img.step[0]*j + k*Img.step[1]);
						*(Img.data + i + Img.step[0]*j + k*Img.step[1]) = 0;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	cout<<"for color image"<<endl;
	cout<<"Img.step[0]="<<Img.step[0]<<" Img.step[1]="<<Img.step[1]<<endl;
	cvtColor(Img,Img,CV_BGR2GRAY);
	
	cout<<"for grayscale image"<<endl;
	cout<<"Img.step[0]="<<Img.step[0]<<" Img.step[1]="<<Img.step[1]<<endl;
	
	namedWindow("Initial");
	imshow("Initial",Img);*/
//-------------------------------------------------------------------------------------------------
	//for RGB or any multiple channel image pixel access
	/*if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat rgbCol = imread(argv[1],1);//1 for RGB image reading
	if(!rgbCol.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",rgbCol);
	vector<Mat> planes;  //planes variable is vector type with Mat as individual element
	split(rgbCol,planes);  //splitting img(which is BGR) into 3 planes and stored in different Mat of planes variable
							//remember planes will be splitted as BGR not RGB

	for(int i=0;i< rgbCol.rows;i++)	    //run throught the rows
	{
		if(i<10)
		{
			for(int j=0;j< rgbCol.cols;j++)//run throught the cols
			{
				if(j<10)
				{
					cout<<(int)planes[0].at<uchar>(i,j)<<"(B)"<<(int)planes[1].at<uchar>(i,j)<<"(G)"
						<<(int)planes[2].at<uchar>(i,j)<<"(R)"<<endl;          //for getting 
					//planes[0].at<uchar>(i,j)=0;				//for setting B
					planes[1].at<uchar>(i,j)=0;				//for setting G
					planes[2].at<uchar>(i,j)=0;				//for setting R
					
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	merge(planes,rgbCol);//opposite of split which merges arrayes of Mat to single multidimensional Mat
	
	namedWindow("Final");
	imshow("Final",rgbCol);*/
//-------------------------------------------------------------------------------------------------------------
	/*if(argc < 2)
	{
		cout<<"fewer argument";
		return -1;
	}
	Mat rgbCol = imread(argv[1],1);//1 for RGB image reading
	if(!rgbCol.data)
	{
		cout<<"image read is error";
		return -1;
	}
	
	namedWindow("Initial");
	imshow("Initial",rgbCol);
	vector<Mat> planes;  //planes variable is vector type with Mat as individual element
	split(rgbCol,planes);  //splitting img(which is BGR) into 3 planes and stored in different Mat of planes variable
							//remember planes will be splitted as BGR not RGB

	for(int i=0;i< rgbCol.rows;i++)	    //run throught the rows
	{
		if(i<10)
		{
			uchar* rowPtr0 = planes[0].ptr<uchar>(i);
			uchar* rowPtr1 = planes[1].ptr<uchar>(i);
			uchar* rowPtr2 = planes[2].ptr<uchar>(i);
			for(int j=0;j< rgbCol.cols;j++)//run throught the cols
			{
				if(j<10)
				{
					cout<<(int)rowPtr0[j]<<"(B)"<<(int)rowPtr1[j]<<"(G)"
						<<(int)rowPtr2[j]<<"(R)"<<endl;          //for getting 
					rowPtr0[j]=0;				//for setting B
					rowPtr1[j]=0;				//for setting G
					rowPtr2[j]=0;				//for setting R
					
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	merge(planes,rgbCol);//opposite of split which merges arrayes of Mat to single multidimensional Mat
	
	namedWindow("Final");
	imshow("Final",rgbCol);*/
	

	waitKey(0);
	return 0;
}
