// opencvtest.cpp : Defines the entry point for the console application.
//

#include "FaceRec.h"
#include "VideoCap.h"
#include "imgProc.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//ImgProc imgp;
	VideoCap vicap;
	//FaceRecognition facerec;
	//imgp.EdgeDetectionsCanny();
	//imgp.SmoothingImage("E:\\lena.png", 25);
	vicap.FaceDetector();
	//vicap.OriginalCapturing();
	system("PAUSE");
	return EXIT_SUCCESS;
}

