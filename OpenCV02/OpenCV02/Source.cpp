/*
	@ver	Used OpenCV version: 3.3.0;
	@desc	Afisam valoarea fiecarui pixel din imagine
	@author	Mihai-Traian Caragheorghiev <caragheorghiev.mihai@gmail.com>
*/
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	// Salvam valoarea intr-o variabila tip matrice
	Mat image = imread("test.png");
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			// Stim ca un pixel este format din (R, G, B)
			// Asa ca afisam valorile de la [0, 255]
			cout << "(";
			cout << (int)image.at<Vec3b>(i, j)[0] << ", ";
			cout << (int)image.at<Vec3b>(i, j)[1] << ", ";
			cout << (int)image.at<Vec3b>(i, j)[2] << ") ";
		}
		cout << endl << endl;
	}
	// La final afisam imaginea.
	imshow("Image", image);
	cvWaitKey(0);
	return 0;
}