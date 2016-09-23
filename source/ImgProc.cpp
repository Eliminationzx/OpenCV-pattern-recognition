#include "ImgProc.h"

void ImgProc::SmoothingImage(const std::string& fileName, const int value)
{
    cv::Mat img, dst;
    img = cv::imread(fileName, 1);
    const std::string window = "Image processing - smoothing image";

    if (img.empty())
    {
        std::cout << "Image is not loaded...." << std::endl;
        return;
    }

    std::cout << "Smoothing level: " << value << std::endl;
    std::cout << "Resolution: " << img.cols << " x " << img.rows << std::endl;
    
    cv::namedWindow(window, 1);
    blur(img, dst, cv::Size(value, value), cv::Point(-1, -1), 4);
    imshow(window, dst);

    cv::waitKey(0);
}

void ImgProc::EdgeDetectionsCanny()
{
    cv::VideoCapture capture;
    cv::Mat original, gray, edge, detectEdges;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::RNG rng(12345);
    const std::string window = "Image processing - edge detection";

    capture.open(0);

    if (!capture.isOpened())
    {
        std::cout << "Camera opened error" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    while (true)
    {
        capture >> original;

        if (!original.empty())
        {
            cvtColor(original, gray, CV_BGR2GRAY); // convert image to gray scale
            blur(original, edge, cv::Size(3, 3)); // blur image
            Canny(edge, detectEdges, 10, 100, 3, true); // detecting edges using canny edge detection

            findContours(detectEdges, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

            cv::Mat drawing = cv::Mat::zeros(detectEdges.size(), CV_8UC3);

            for (int i = 0; i< int(contours.size()); i++)
            {
                drawContours(original, contours, i, cv::Scalar(0, 0, 255), 1, 8, hierarchy, 0, cv::Point());
            }
            
            imshow(window, original);
        }
        if (cv::waitKey(30) >= 0) break;
    }
}