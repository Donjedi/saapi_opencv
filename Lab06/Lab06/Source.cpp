/*
	@Desc	Laboratorul 6
	@Author	Mihai-Traian Caragheorghiev
	@ver	3.3.0
*/

#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Histogram1D.h"

#define CA_Q_POZ = 1.5;
#define CA_Q_NEG = -1.5;

using namespace cv;

Mat MedieArmonica(Mat imagine, float q)
{
	Mat rezultat;
	Mat_<Vec3b>::iterator it = imagine.begin<Vec3b>();
	Mat_<Vec3b>::iterator end = imagine.end<Vec3b>();
	
	return rezultat;
}

Mat MedieAritmetica(Mat imagine)
{
	Mat rezultat;
	Mat_<Vec3b>::iterator it = imagine.begin<Vec3b>();
	Mat_<Vec3b>::iterator end = imagine.end<Vec3b>();

	return rezultat;
}

Mat MedieGeometrica(Mat imagine)
{
	Mat rezultat;
	Mat_<Vec3b>::iterator it = imagine.begin<Vec3b>();
	Mat_<Vec3b>::iterator end = imagine.end<Vec3b>();

	return rezultat;
}

int main()
{
	// Tema 1:
	Mat imagine1, imagine1a, imagine1b, imagine1c, imagine1d, imagine1e, imagine1f;
	Histogram1D hist;

	imagine1 = imread("test1.jpg");
	imagine1a = imread("test1a.jpg");
	imagine1b = imread("test1b.jpg");
	imagine1c = imread("test1c.jpg");
	imagine1d = imread("test1d.jpg");
	imagine1e = imread("test1e.jpg");
	imagine1f = imread("test1f.jpg");
	
	cv::namedWindow("Imagine");
	cv::imshow("Imagine", imagine1);
	cv::namedWindow("Histogram");
	cv::imshow("Histogram", hist.getHistogramImage(imagine1));
	waitKey(0);

	cv::imshow("Imagine", imagine1a);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1a));
	waitKey(0);

	cv::imshow("Imagine", imagine1b);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1b));
	waitKey(0);

	cv::imshow("Imagine", imagine1c);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1c));
	waitKey(0);

	cv::imshow("Imagine", imagine1d);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1d));
	waitKey(0);

	cv::imshow("Imagine", imagine1e);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1e));
	waitKey(0);

	cv::imshow("Imagine", imagine1f);
	cv::imshow("Histogram", hist.getHistogramImage(imagine1f));
	waitKey(0);
	cvDestroyAllWindows();

	// Tema 2:
	/*Mat circ, circ1, rezultat, rezultat2;
	cvNamedWindow("Imagine Originala");
	cvNamedWindow("Zgomot Gaussian");
	circ = imread("circ.jpg");
	circ1 = imread("circ1.jpg");
	imshow("Imagine Originala", circ);
	imshow("Zgomot Gaussian", circ1);
	waitKey(0);
	medianBlur(circ1, rezultat, 5);
	imshow("Rezultat Medie Aritmetica", rezultat);
	imshow("Rezultat Medie Geometrica", rezultat2);
	waitKey(0);*/

	// Tema 3
	Mat circ2, circ3, ca_poz, ca_neg;
	circ2 = imread("circ2.jpg");
	circ3 = imread("circ3.jpg");


	// Tema 4
	Mat circ4, ma, median;
	circ4 = imread("circ4.jpg");
	cvNamedWindow("Imagine");
	
	medianBlur(circ4, median, 5);
	imshow("Imagine", circ4);
	waitKey(0);
	//cvNamedWindow("Filtru Medie Aritmetica");
	//imshow("Filtru Medie Aritmetica", ma);
	cvNamedWindow("Filtru Median");
	imshow("Filtru Median", median);
	waitKey(0);
	
	return 0;
}