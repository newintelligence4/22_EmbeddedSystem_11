#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <photo.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
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
		//img = imread(argv[1], IMREAD_COLOR);//카메라에 잡히는 img load
	}
	else {
		max = 50;
	}

	Mat gray(frame_height, frame_width, CV_8UC1);
	Mat sobel;
	int R_val, G_val, B_val;
	float average_gray;
	while (count <= max) {
		cap.read(img);
		if (img.empty()) break;
		count++;

		//color img를 gray scale로 변환
		for (int i = 0; i < frame_height; i++) {
			for (int j = 0; j < frame_width; j++) {
				R_val = img.at<Vec3b>(i, j)[2];
				B_val = img.at<Vec3b>(i, j)[1];
				G_val = img.at<Vec3b>(i, j)[0];

				average_gray = (int)((R_val + G_val + B_val) / 3);

				gray.at<uchar>(i, j) = average_gray;
			}
		}

		//gray scale img를 sobel 함수를 이용해 sobel img 출력
		Sobel(gray, sobelX, CV_8U, 1, 0);
		Sobel(gray, sobelY, CV_8U, 0, 1);
		sobel = abs(sobelX) + abs(sobelY);

		video.write(sobel);//write
	}

	cap.release();
	video.release();
	return 0;
}




