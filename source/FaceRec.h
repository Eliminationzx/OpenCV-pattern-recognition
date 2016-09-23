#ifndef __FACEREC_H
#define __FACEREC_H

#include <iostream>
#include <string>
#include <vector>
#include <omp.h>

// include opencv core
#include "opencv2\core\core.hpp"
#include "opencv2\contrib\contrib.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\opencv.hpp"

// file handling
#include <fstream>
#include <sstream>

#define OPENCV_CASCADE "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"

#define RED     CV_RGB(255, 0, 0)
#define GREEN   CV_RGB(0, 255, 0)
#define BLUE    CV_RGB(0, 0, 255)
#define YELLOW  CV_RGB(255, 255, 0)
#define PURPLE  CV_RGB(255, 0, 255)
#define GREY    CV_RGB(200, 200, 200)

class FaceRecognition
{
public:
    // Create and return normalize image
    static cv::Mat MatNorm(cv::InputArray _src)
    {
        cv::Mat src = _src.getMat();
        cv::Mat dst;
        for (int i = 1; i < src.channels(); i++)
            normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC(i));
        src.copyTo(dst);
        return dst;
    }

    void DBRead(const std::string& fileName, char separator = ';'); // read from data storage
   
    /* Trainer's algorithms */
    void EigenFaceTrainer(const std::string fileName); // algorithm eigenface recognizer
    void FisherFaceTrainer(const std::string fileName); // algorithm fisherface recognizer
    void LBPHFaceTrainer(const std::string fileName); // lbph recognizer model

    void Execute(const std::string fileName, const std::string grayScale);

private:
    std::vector<cv::Mat> _img;
    std::vector<int> _labels;
};

#endif