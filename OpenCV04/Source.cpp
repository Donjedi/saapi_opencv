/*
	@ver	Used OpenCV version: 3.3.0;
	@desc	Modificam valorile pixelilor imaginii .bmp cu valori aleatorii
	@author	Mihai-Traian Caragheorghiev <caragheorghiev.mihai@gmail.com>
*/

#include <opencv2\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Declarare functii;
Mat schimbareCuloarePixeli(Mat imagine);
void afisareImagineRedimensionata(Mat imagine);

int main()
{
	// Citire imagine
	Mat imagine = imread("test.bmp", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_COLOR);

	// Prelucrare imagine
	imagine = schimbareCuloarePixeli(imagine);

	// Afisare imagine
	afisareImagineRedimensionata(imagine);

	// Salvare imagine noua
	imwrite("ImagineNoua.bmp", imagine);

	waitKey(0);
	return 0;
}

void afisareImagineRedimensionata(Mat imagine)
{
	Mat output;
	resize(imagine, output, Size(), 32, 32, CV_INTER_AREA);
	imshow("Image", output);
}

Mat schimbareCuloarePixeli(Mat imagine)
{
	for (int i = 0; i < imagine.rows; i++)
	{
		for (int j = 0; j < imagine.cols; j++)
		{
			// Stim ca un pixel este format din (R, G, B)
			// Asa ca alegem aleatoriu valorile de la [0, 255]
			imagine.at<Vec3b>(i, j)[0] = rand() % 255;
			imagine.at<Vec3b>(i, j)[1] = rand() % 255;
			imagine.at<Vec3b>(i, j)[2] = rand() % 255;
		}
	}

	return imagine;
}