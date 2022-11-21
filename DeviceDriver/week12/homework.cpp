#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	
	int max = 0, count = 0;
	VideoCapture cap;
	cap.open("/dev/video0", CAP_V4L2);
	if (!cap.isOpened()) {
		printf("Can't open Camera\n");
		return -1;
	}

	//Default resolutions of the frame are obtained.The resolutions are system dependent.
	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	//Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
	VideoWriter video("homework.avi",cv::VideoWriter::fourcc('M','J','P','G'),10,Size(frame_width,frame_height));

	printf("Open Camera\n");

	if (argc > 1) {
		max = int(argv[1]);
		//img = imread(argv[1], IMREAD_COLOR);//ī�޶� ������ img load
	}
	else {
		max = 50;
	}

	Mat sobel, img, sobelX, sobelY;

	while (count <= max) {
		cap.read(img);
		if (img.empty()) break;
		
		Sobel(img, sobelX, CV_8U, 1, 0);
		Sobel(img, sobelY, CV_8U, 0, 1);
		sobel = abs(sobelX) + abs(sobelY);

		video.write(sobel);//write
		count++;
	}

	cap.release();
	video.release();
	return 0;
}

//g++ -o homework homework.cpp $(pkg-config opencv4 --libs --cflags)
