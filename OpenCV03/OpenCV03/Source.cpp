/*
	@ver	Used OpenCV version: 3.3.0;
	@desc	Afisam caracteristicile imaginii .bmp
	@author	Mihai-Traian Caragheorghiev <caragheorghiev.mihai@gmail.com>
*/

#include <opencv2\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Declarare functii
void afisareDetaliiPixeli(Mat imagine);
void afisareImagineRedimensionata(Mat imagine);

int main()
{
	Mat image = imread("test.bmp", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	
	cout << "Canale de culoare: " << image.channels() << endl;
	cout << "Tip Imagine: " << image.type() << " bytes" << endl;
	cout << "Adancimea culorii: " << image.depth() << endl;
	cout << "Latime: " << image.rows << " pixels" << endl;
	cout << "Inaltime: " << image.cols << " pixels" << endl;
	cout << "Marimea Imaginii: " << image.size << endl;
	cout << "Dimensiunea Fisierului: " << image.rows * image.cols * image.channels() << " bytes" << endl;
	
	// Afisam Detaliile (R, G, B) ale pixelilor
	afisareDetaliiPixeli(image);
	
	// Afisare imagine pentru analizare
	afisareImagineRedimensionata(image);
	cvWaitKey(0);
	return 0;
}

/*
	@Mat  imagine primeste o imagine sub forma de matrice
	@desc Functia se ocupa cu afisatul detaliilor valorilor pixelilor din imagine
*/
void afisareDetaliiPixeli(Mat imagine)
{
	for (int i = 0; i < imagine.rows; i++)
	{
		cout << endl;
		for (int j = 0; j < imagine.cols; j++)
		{
			// Stim ca un pixel este format din (R, G, B)
			// Asa ca afisam valorile de la [0, 255]
			cout << "(";
			cout << (int)imagine.at<Vec3b>(i, j)[0] << ", ";
			cout << (int)imagine.at<Vec3b>(i, j)[1] << ", ";
			cout << (int)imagine.at<Vec3b>(i, j)[2] << ") ";
		}
		cout << endl;
	}
}

/*
	@Mat  imagine primeste o imagine sub forma de matrice
	@desc Redimensionarea imaginii pentru a putea fi vizualizata si analizata
*/
void afisareImagineRedimensionata(Mat imagine)
{
	Mat output;
	resize(imagine, output, Size(), 32, 32, CV_INTER_AREA);
	imshow("Image", output);
}