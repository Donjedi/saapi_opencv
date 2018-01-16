// include the necessary function definitions
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#pragma warning(disable:4996)

int ex2()
{
	IplImage* image2;

	//deschid fisierul imagine
	image2 = cvLoadImage("discuri.jpg", -1);
	if (image2 == NULL || image2->imageData == NULL)
		return -1;

	IplImage* gray = cvCreateImage(cvGetSize(image2), IPL_DEPTH_8U, 1);
	IplImage *opening = cvCreateImage(cvGetSize(image2), IPL_DEPTH_8U, 1);
	IplImage* closing = cvCreateImage(cvGetSize(image2), IPL_DEPTH_8U, 1);
	IplImage* eroded2 = cvCreateImage(cvGetSize(image2), IPL_DEPTH_8U, 1);
	IplImage* border2 = cvCreateImage(cvGetSize(image2), IPL_DEPTH_8U, 1);
	cvCvtColor(image2, gray, CV_BGR2GRAY);
	image2 = gray;
	cvNamedWindow("discuri", 1);
	cvShowImage("discuri", image2);
	cvWaitKey(0);

	int *val;
	int center = 1;
	int ker_size = 3;
	//for(int ker_size = 3; ker_size <= 21; ker_size += 2, center++)
	{
		val = new int[ker_size << 1];
		memset(val, 1, (ker_size << 1) * sizeof(int));

		IplConvKernel* kernel = cvCreateStructuringElementEx(19, 19, 9, 9, CV_SHAPE_RECT, val);

		cvMorphologyEx(image2, closing, NULL, kernel, CV_MOP_CLOSE, 2);
		/*cvNamedWindow("inchidere", 1);
		cvShowImage("inchidere", closing);
		cvWaitKey(0);*/

		delete val;
	}

	center = 1;
	//for(ker_size = 3; ker_size <= 39; ker_size += 2, center++)
	{
		val = new int[ker_size << 1];
		memset(val, 1, (ker_size << 1) * sizeof(int));

		IplConvKernel* kernel = cvCreateStructuringElementEx(39, 39, 18, 18, CV_SHAPE_RECT, val);

		cvMorphologyEx(closing, opening, NULL, kernel, CV_MOP_OPEN, 2);
		/*cvNamedWindow("deschidere", 1);
		cvShowImage("deschidere", opening);
		cvWaitKey(0);*/

		delete val;
	}

	cvThreshold(opening, opening, 200, 255, CV_THRESH_BINARY);
	/*cvNamedWindow("prag", 1);
	cvShowImage("prag", opening);
	cvWaitKey(0);*/

	int values9x9[81] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1 };
	IplConvKernel* kernel = cvCreateStructuringElementEx(9, 9, 5, 5, CV_SHAPE_RECT, values9x9);

	cvErode(opening, eroded2, kernel, 1);
	/*cvNamedWindow("Erodat3x3", 1);
	cvShowImage("Erodat3x3", eroded2);
	cvWaitKey(0);*/

	cvAbsDiff(opening, eroded2, border2);
	/*cvNamedWindow("Border", 1);
	cvShowImage("Border", border2);
	cvWaitKey(0);*/

	cvAdd(image2, border2, image2);
	cvNamedWindow("segmentation", 1);
	cvShowImage("segmentation", image2);
	cvWaitKey(0);

	return 0;
}

int ex1()
{
	IplConvKernel* element = 0;

	IplImage *pInputImage = cvLoadImage("lena.jpg", 1);
	if (pInputImage == NULL)
		return -1;

	IplImage *pGrayImage = cvCreateImage(cvGetSize(pInputImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pInputImage, pGrayImage, CV_RGB2GRAY);

	// no need for input image
	cvReleaseImage(&pInputImage);
	pInputImage = NULL;

	cvNamedWindow("orig", 1);
	cvShowImage("orig", pGrayImage);
	cvWaitKey(0);
	cvDestroyWindow("orig");

	IplImage *pOutputImage = cvCloneImage(pGrayImage);

	element = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_RECT, 0);

	// dilate
	cvDilate(pGrayImage, pOutputImage, element);
	cvNamedWindow("dilate", 1);
	cvShowImage("dilate", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("dilate");

	// erode
	cvErode(pGrayImage, pOutputImage, element);
	cvNamedWindow("erode", 1);
	cvShowImage("erode", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("erode");

	// open
	cvMorphologyEx(pGrayImage, pOutputImage, NULL, element, CV_MOP_OPEN);
	cvNamedWindow("open", 1);
	cvShowImage("open", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("open");

	// close
	cvMorphologyEx(pGrayImage, pOutputImage, NULL, element, CV_MOP_CLOSE);
	cvNamedWindow("close", 1);
	cvShowImage("close", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("close");

	// smooth
	cvMorphologyEx(pGrayImage, pOutputImage, NULL, element, CV_MOP_OPEN);
	cvMorphologyEx(pOutputImage, pOutputImage, NULL, element, CV_MOP_CLOSE);
	cvNamedWindow("smooth", 1);
	cvShowImage("smooth", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("smooth");

	// gradient
	IplImage *pTmp = cvCreateImage(cvGetSize(pGrayImage), IPL_DEPTH_8U, 1);
	cvMorphologyEx(pGrayImage, pOutputImage, pTmp, element, CV_MOP_GRADIENT);
	cvNamedWindow("gradient", 1);
	cvShowImage("gradient", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("gradient");
	cvReleaseImage(&pTmp);
	pTmp = NULL;

	// tophat
	cvMorphologyEx(pGrayImage, pOutputImage, pTmp, element, CV_MOP_TOPHAT);
	cvNamedWindow("tophat", 1);
	cvShowImage("tophat", pOutputImage);
	cvWaitKey(0);
	cvDestroyWindow("tophat");

	cvReleaseStructuringElement(&element);

	//release images
	cvReleaseImage(&pGrayImage);
	cvReleaseImage(&pOutputImage);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ex1();
	ex2();
	return 0;
}