#ifndef __IMGPROC_H
#define __IMGPROC_H

#include <iostream>
#include <string>
#include <vector>

// include opencv core
#include "opencv2\core\core.hpp"
#include "opencv2\contrib\contrib.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\opencv.hpp"

// file handling
#include <fstream>
#include <sstream>

class ImgProc
{
public:
    void SmoothingImage(const std::string& fileName, const int value);
    void EdgeDetectionsCanny();
};

#endif