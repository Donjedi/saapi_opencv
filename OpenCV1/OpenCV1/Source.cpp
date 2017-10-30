#include <opencv2\core\core.hpp>
#include <opencv\cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/// Global Variables
int MAX_KERNEL_LENGTH = 21;

void afisareImagineRedimensionata(Mat imagine, int multiplicator)
{
	Mat output;
	resize(imagine, output, Size(), multiplicator, multiplicator, CV_INTER_AREA);
	imshow("Image", output);
}

int main()
{
	// Citire imagine
	Mat median, medie, tmp, dst;
	Mat imagine = imread("circ4.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_COLOR);
	Mat test = imread("test.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_COLOR);

	// Filtru Median
	/*for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(imagine, median, i);
		afisareImagineRedimensionata(median, 2);
		waitKey(0);
	}*/

	/*for (int i = 1; i <= 30; i++) {
		for (int j = 1; j <= 30; j++) {
			pyrMeanShiftFiltering(imagine, medie, i, j, 3);
			afisareImagineRedimensionata(medie, 2);
			cout << i << ", " << j << endl;
			waitKey(0);
		}
	}*/

	// Filtru Medie Aritmetica
	pyrMeanShiftFiltering(imagine, medie, 5, 40, 3);
	afisareImagineRedimensionata(medie, 2);
	waitKey(0);


	// Filtru Trecere sus
	
		tmp = test;
		dst = tmp;
		pyrUp(tmp, dst, CV_GAUSSIAN_5x5);
		namedWindow("PyrUp", CV_WINDOW_AUTOSIZE);
		imshow("PyrUp", dst);
		waitKey();

	return 0;
}

