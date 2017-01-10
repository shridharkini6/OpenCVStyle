#include <iostream>
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;
//By Shridhar Kini(Subscribe to: OpenCVstyle in YouTube)
int main( int argc, char** argv )
{
	//VideoCapture camera(0);
	VideoCapture camera("K:/videoSongs/thats_my_name_akcent_HD1080p.mp4");
	//camera.open(0);
	if(!camera.isOpened())
	{
		cerr<<"Camera did not loaded properly"<<endl;
		return -1;
	}
	Mat frame;
	//camera.set(CV_CAP_PROP_FRAME_WIDTH,320);
	//camera.set(CV_CAP_PROP_FRAME_HEIGHT,240);
	namedWindow("Camer Capture");
	while(1)
	{
		camera>>frame;
		//camera.read(frame);
		//camera.retrieve(frame,0);
		if(frame.empty())
		{
			cout<<camera.get(CV_CAP_PROP_FRAME_WIDTH)<<"X"<<camera.get(CV_CAP_PROP_FRAME_HEIGHT);
			cerr<<"Could not load frame"<<endl;
			continue;
		}
		imshow("Camer Capture",frame);
		int key=waitKey(30);
		if(key == 27)
		{
			break;
		}
	}
	waitKey(0);
	return 0;
}
