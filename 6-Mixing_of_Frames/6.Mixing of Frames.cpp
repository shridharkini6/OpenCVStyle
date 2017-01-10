#include <iostream>
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;
//By Shridhar Kini(Subscribe to: OpenCVstyle in YouTube)
int main( int argc, char** argv )
{
	VideoCapture camera(0);
	VideoCapture file1("K:/videoSongs/Akcent_Chimie_Intre_Noi.mp4");//do not use backward slash(\)
	if(!camera.isOpened())
	{
		cerr<<"Camera did not loaded properly"<<endl;
		return -1;
	}
	if(!file1.isOpened())
	{
		cerr<<"file1 could not be opened";
		return -1;
	}
	Mat CamFrame,file1Frame;
	camera.set(CV_CAP_PROP_FRAME_WIDTH,640);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	namedWindow("MixedFrames");
	while(1)
	{
		camera>>CamFrame;//capturing frame from camera
		if(CamFrame.empty())
		{
			cout<<camera.get(CV_CAP_PROP_FRAME_WIDTH)<<"X"<<camera.get(CV_CAP_PROP_FRAME_HEIGHT);
			cerr<<"Could not load frame"<<endl;
			continue;
		}
		if(!file1.grab())
		{
			cerr<<"no frame in file1"<<endl;
			return -1;
		}
		file1.read(file1Frame);//capturing frame from file1

		//resize the video's from file so that it can fit into proper rectangle
		Mat t(480,640,CV_8UC3);
		resize(file1Frame,t,t.size(),0,0,CV_INTER_AREA);

		Mat finalFrame(960,640,CV_8UC3); // resulting frame
		finalFrame.setTo(0);
		vector<Mat> camPlanes,file1Planes,finalPlanes;// to access each pixel values vector type of Mat is needed
		
		//split the rgb components into vector variable
		split(CamFrame,camPlanes);
		split(t,file1Planes);
		split(finalFrame,finalPlanes);
		
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<960;j++)
			{
				uchar* xCam;
				uchar* xfile1;
				uchar* xfinal = finalPlanes[i].ptr<uchar>(j);
				if(j < 480)
				{
					xfile1= file1Planes[i].ptr<uchar>(j);
				}
				else
				{
						xCam= camPlanes[i].ptr<uchar>(j-480);	
				}
				
				for(int k=0;k<640;k++)
				{
					if(j < 480)
					{
						xfinal[k] = xfile1[k] ;
					}
					else
					{
						xfinal[k] = xCam[k];
					}
				}
			}
		}
		merge(finalPlanes,t);
		imshow("MixedFrames",t);
		int key=waitKey(20);
		if(key == 27)
		{
			break;
		}
	}
	waitKey(0);
	return 0;
}
