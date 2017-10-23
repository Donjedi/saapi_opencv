/*
	@ver	Used OpenCV version: 3.3.0;
	@desc	Afisare histograme
	@author	Mihai-Traian Caragheorghiev <caragheorghiev.mihai@gmail.com>
*/

#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

/*
	@string const& name Variabila ce primeste numele ferestrei pentru afisarea Histogramei
	@Mat1b const& image	Variabila ce primeste imaginea pentru care se face histograma(numai grayscale)
*/
void arataHistograma(std::string const& name, Mat1b const& image)
{
	// Setare numar maxim de intervale din histograma
	int bins = 256;
	int histSize[] = { bins };

	// Setare interval de valori pentru histograma
	float lranges[] = { 0, 256 };
	const float* ranges[] = { lranges };

	// Creare matrice pentru histograma
	Mat hist;
	int channels[] = { 0 };

	// Creare matrice pentru vizualizare histograma
	int const hist_height = 256;
	Mat3b hist_image = Mat3b::zeros(hist_height, bins);

	// Functie pentru calcularea Histogramei
	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
	double max_val = 0;
	minMaxLoc(hist, 0, &max_val);

	// Desenare fiecare linie din histograma
	for (int b = 0; b < bins; b++) {
		float const binVal = hist.at<float>(b);
		int   const height = cvRound(binVal*hist_height / max_val);
		line
		(hist_image
			, Point(b, hist_height - height), Point(b, hist_height)
			, Scalar::all(255)
		);
	}
	imshow(name, hist_image);
}

int main()
{
	// Incarcare imagine
	Mat3b const imagine = imread("test.jpg", IMREAD_COLOR);
	
	// Transformare imagine in spectrul gri
	Mat1b imgGri;
	cvtColor(imagine, imgGri, COLOR_BGR2GRAY);
	
	// Afisare imagine initiala
	imshow("Imagine", imagine);
	waitKey();

	// Afisare imagine din spectrul gri
	imshow("Imagine", imgGri);

	// Afisare histograma
	arataHistograma("Histograma", imgGri);
	waitKey();

	// Creem o noua matrice pentru histograma egalizata
	Mat1b egalizareHistograma;
	equalizeHist(imgGri, egalizareHistograma);
	
	// Afisam noua imagine in functie de histograma egalizata
	imshow("Img Histograma", egalizareHistograma);
	arataHistograma("HistogramaEgaliata", egalizareHistograma);
	waitKey();

	return 0;
}