// include the necessary function definitions
#include <conio.h>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <stdio.h>
#include <tchar.h>

// link the necessary libraries
//#pragma comment (lib, "cv.lib")
//#pragma comment (lib, "cxcore.lib")
//#pragma comment (lib, "highgui.lib")

// define lower and upper threshold values for Canny edge detection
#define LOWER_THRESHOLD 50
#define UPPER_THRESHOLD 150

// define parameters used by the progressive probabilistic Hough transform
#define RHO			1
#define THETA		CV_PI/180
#define THRESHOLD	50
#define PARAM1		50
#define PARAM2		10

// define names for windows and images to be used
const char* NAME[] = { "Original", "Grayscaled", "Canny Edge Detector", "Hough Line Detector", "Hough Circle Detector" };
const char* IMAGE[] = { "baboon.jpg", "airplane.jpg", "airplaneF16.jpg", "lena.jpg", "parthenon.jpg", "mira.jpg" };


/*
Se considera imaginile "baboon.jpg", "airplane.jpg", airplaneF16.jpg" si "lena.jpg" (imaginile color se vor
transforma la niveluri de gri) pentru care se va realiza detectarea de contur pe baza algoritmului Canny. Sa
se compare rezultatele obtinute cu celelalte solutii pentru detectarea de contur.
*/
void Task1(const char* pImageName)
{
	////// load input image
	IplImage* pOriginalInputImage = cvLoadImage(pImageName, 1);
	if (pOriginalInputImage == NULL)
	{
		return;
	}

	// create window and display the image
	cvNamedWindow(NAME[0], 1);
	cvShowImage(NAME[0], pOriginalInputImage);
	cvWaitKey(0);

	////// convert to grayscale
	IplImage* pInputImage = cvCreateImage(cvGetSize(pOriginalInputImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pOriginalInputImage, pInputImage, CV_RGB2GRAY);

	// create window and display the image
	cvNamedWindow(NAME[1], 1);
	cvShowImage(NAME[1], pInputImage);
	cvWaitKey(0);

	////// apply Canny
	IplImage* pOutputImage = cvCloneImage(pInputImage);
	cvCanny(pOutputImage, pOutputImage, LOWER_THRESHOLD, UPPER_THRESHOLD);

	// create window and display the image
	cvNamedWindow(NAME[2], 1);
	cvShowImage(NAME[2], pOutputImage);
	cvWaitKey(0);

	////// cleanup
	cvReleaseImage(&pOriginalInputImage);
	cvReleaseImage(&pInputImage);
	cvReleaseImage(&pOutputImage);
	for (int i = 0; i<3; i++)
	{
		cvDestroyWindow(NAME[i]);
	}
}


/*
Pe baza transformarii Hough pentru linii sa se identifice liniile din imaginea "parthenon.jpg".
*/
void Task2(const char* pImageName)
{
	////// load input image
	IplImage* pOriginalInputImage = cvLoadImage(pImageName, 1);
	if (pOriginalInputImage == NULL)
	{
		return;
	}

	// create window and display the image
	cvNamedWindow(NAME[0], 1);
	cvShowImage(NAME[0], pOriginalInputImage);
	cvWaitKey(0);

	////// convert to grayscale
	IplImage* pInputImage = cvCreateImage(cvGetSize(pOriginalInputImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pOriginalInputImage, pInputImage, CV_RGB2GRAY);

	// create window and display the image
	cvNamedWindow(NAME[1], 1);
	cvShowImage(NAME[1], pInputImage);
	cvWaitKey(0);

	////// apply Canny to create a binary image
	IplImage* pAuxImage = cvCloneImage(pInputImage);
	IplImage* pOutputImage = cvCreateImage(cvGetSize(pAuxImage), 8, 3);
	cvCanny(pAuxImage, pAuxImage, LOWER_THRESHOLD, UPPER_THRESHOLD);
	cvCvtColor(pAuxImage, pOutputImage, CV_GRAY2BGR);

	// apply the Hough transform to find the lines
	CvMemStorage* pStorage = cvCreateMemStorage(0);
	CvSeq* pLines = cvHoughLines2(pAuxImage, pStorage, CV_HOUGH_PROBABILISTIC, RHO, THETA, THRESHOLD, PARAM1, PARAM2);
	for (int i = 0; i<pLines->total; i++)
	{
		CvPoint* pPoint = (CvPoint*)cvGetSeqElem(pLines, i);
		cvLine(pOutputImage, pPoint[0], pPoint[1], CV_RGB(0, 255, 0), 3, CV_AA, 0);
	}

	// create window and display the image
	cvNamedWindow(NAME[3], 1);
	cvShowImage(NAME[3], pOutputImage);
	cvWaitKey(0);

	////// cleanup
	for (int i = 0; i<4; i++)
	{
		if (i == 2)
		{
			i++;
		}
		cvDestroyWindow(NAME[i]);
	}
	cvClearMemStorage(pStorage);
	cvClearSeq(pLines);
	cvReleaseImage(&pOriginalInputImage);
	cvReleaseImage(&pInputImage);
	cvReleaseImage(&pAuxImage);
	cvReleaseImage(&pOutputImage);
}

/*
Pe baza transformarii Hough pentru cercuri sa se identifice cercurile din imaginea "mira.jpg".
*/
void Task3(const char* pImageName)
{
	////// load input image
	IplImage* pOriginalInputImage = cvLoadImage(pImageName, 1);
	if (pOriginalInputImage == NULL)
	{
		return;
	}

	// create window and display the image
	cvNamedWindow(NAME[0], 1);
	cvShowImage(NAME[0], pOriginalInputImage);
	cvWaitKey(0);

	////// convert to grayscale
	IplImage* pInputImage = cvCreateImage(cvGetSize(pOriginalInputImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pOriginalInputImage, pInputImage, CV_RGB2GRAY);

	// create window and display the image
	cvNamedWindow(NAME[1], 1);
	cvShowImage(NAME[1], pInputImage);
	cvWaitKey(0);

	////// smooth the image for better results
	IplImage* pAuxImage = cvCloneImage(pInputImage);
	IplImage* pOutputImage = cvCreateImage(cvGetSize(pAuxImage), 8, 3);
	cvSmooth(pAuxImage, pAuxImage, CV_GAUSSIAN, 5, 5);
	cvCvtColor(pAuxImage, pOutputImage, CV_GRAY2BGR);

	// apply the Hough transform to find the circles
	CvMemStorage* pStorage = cvCreateMemStorage(0);
	CvSeq* pCircles = cvHoughCircles(pAuxImage, pStorage, CV_HOUGH_GRADIENT, 1, pAuxImage->width / 4);
	for (int i = 0; i<pCircles->total; i++)
	{
		float* pValues = (float*)cvGetSeqElem(pCircles, i);
		CvPoint Center = cvPoint(cvRound(pValues[0]), cvRound(pValues[1]));
		cvCircle(pOutputImage, Center, cvRound(pValues[2]), CV_RGB(0, 255, 0), 5);
	}

	// create window and display the image
	cvNamedWindow(NAME[4], 1);
	cvShowImage(NAME[4], pOutputImage);
	cvWaitKey(0);

	////// cleanup
	for (int i = 0; i<5; i++)
	{
		if (i == 2)
		{
			i += 2;
		}
		cvDestroyWindow(NAME[i]);
	}
	cvClearMemStorage(pStorage);
	cvClearSeq(pCircles);
	cvReleaseImage(&pOriginalInputImage);
	cvReleaseImage(&pInputImage);
	cvReleaseImage(&pOutputImage);
}

// the main program
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Apasati 1 pentru Canny;\n");
	printf("Apasati 2 pentru transformari Hought -> pantheon;\n");
	printf("Apasati 3 pentru transformari Hought -> mira;\n");
	printf("Apasati 0 pentru a iesi.");
	while (true)
	{
		switch (_getch())
		{
		case '1':
		{
			for (int i = 0; i<4; i++)
			{
				Task1(IMAGE[i]);
			}

			break;
		}

		case '2':
		{
			Task2(IMAGE[4]);

			break;
		}

		case '3':
		{
			Task3(IMAGE[5]);

			break;
		}

		case '0':
		{
			exit(0);
		}
		}
	}

	return 0;
}
