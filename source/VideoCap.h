#ifndef __VIDEOCAP_H
#define __VIDEOCAP_H

#include <iostream>
#include <string>
#include <vector>

// include opencv core
#include "opencv2\core\core.hpp"
#include "opencv2\contrib\contrib.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\opencv.hpp"
#include <opencv2/imgproc/imgproc_c.h>

// file handling
#include <fstream>
#include <sstream>
#include <ctime>
#include <omp.h>

#define OPENCV_FACE "C:/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml"

#define RED     CV_RGB(255, 0, 0)
#define GREEN   CV_RGB(0, 255, 0)
#define BLUE    CV_RGB(0, 0, 255)
#define YELLOW  CV_RGB(255, 255, 0)
#define PURPLE  CV_RGB(255, 0, 255)
#define GREY    CV_RGB(200, 200, 200)

#define NUM_FINGERS	5
#define NUM_DEFECTS	8

class VideoCap
{
public:
    void CannyEdgeDetector(); // Edge detection
    void OriginalCapturing(); // Simple video capturing

    void FaceDetector(); // Face detection
    void HandDetector(); // Hand detection
};

#endif