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
	VideoWriter video("outcpp.avi",cv::VideoWriter::fourcc('M','J','P','G'),10,Size(frame_width,frame_height));

	printf("Open Camera\n");
	Mat img;

	if (argc > 1) {
		max = int(argv[1]);
		//img = imread(argv[1], IMREAD_COLOR);//ī�޶� ������ img load
	}
	else {
		max = 50;
	}

	Mat gray(frame_height, frame_width, CV_8UC1);
	Mat sobel, sobelX, sobelY;
	int R_val, G_val, B_val;
	float average_gray;
	while (count <= max) {
		cap.read(img);
		if (img.empty()) break;
		count++;

		//color img�� gray scale�� ��ȯ
		for (int i = 0; i < frame_height; i++) {
			for (int j = 0; j < frame_width; j++) {
				R_val = img.at<Vec3b>(i, j)[2];
				B_val = img.at<Vec3b>(i, j)[1];
				G_val = img.at<Vec3b>(i, j)[0];

				average_gray = (int)((R_val + G_val + B_val) / 3);

				gray.at<uchar>(i, j) = average_gray;
			}
		}

		//gray scale img�� sobel �Լ��� �̿��� sobel img ���
		Sobel(gray, sobelX, CV_8U, 1, 0);
		Sobel(gray, sobelY, CV_8U, 0, 1);
		sobel = abs(sobelX) + abs(sobelY);

		video.write(sobel);//write
	}

	cap.release();
	video.release();
	return 0;
}

//g++ -o homework homework.cpp $(pkg-config opencv4 --libs --cflags)


