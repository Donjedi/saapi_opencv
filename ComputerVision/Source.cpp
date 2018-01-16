#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <windows.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	VideoCapture cap(0);
	cap.open(0);

	Mat img;
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt2.xml"); // xml predefinit OpenCV

	bool loop = true;
	while (loop)
	{
		// Transformare imagini flux video catre mat
		cap >> img;
		cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
		resize(img, img, Size(1000, 640));
		// dreptunghi fata
		vector<Rect> faces;
		// Detectare fete
		face_cascade.detectMultiScale(img, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(140, 140));
		// Afisare rezultat
		// Deseneaza cercuri pe fete
		for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(img, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		// Desenare dreptunghi in jurul capului
		 for (unsigned i = 0; i<faces.size(); i++)
		rectangle(img,faces[i], Scalar(255, 0, 0), 2, 1);

		imshow("Recunoastere Faciala", img);
		int key2 = waitKey(16); // pentru a avea 60 fps (1/60fps)* 1000

		if (GetKeyState(VK_RETURN))
		{
			loop = false;
		}
	}
	return 0;
}