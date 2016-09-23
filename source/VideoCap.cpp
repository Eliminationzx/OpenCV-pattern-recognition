#include "VideoCap.h"

void VideoCap::FaceDetector()
{
    cv::CascadeClassifier face_cascade;
    const std::string window = "Capture - face detection";
    const std::string classifier = OPENCV_FACE;

    long int frameCounter = 0;
    int width = 0, height = 0, tick = 0;

    double fps = 0.0;

    std::vector<cv::Rect> faces;
    cv::Mat frame;
    cv::Mat graySacleFrame;
    cv::Mat cropImg;
    cv::Rect roi;

    if (!face_cascade.load(classifier))
    {
        std::cout << " Error loading file" << std::endl;
        return;
    }

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "exit" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    std::time_t timeBegin = std::time(0);

    while (cv::waitKey(30) < 0)
    {
        cap.read(frame);
        ++frameCounter;

        std::time_t timeNow = std::time(0) - timeBegin;

        if (timeNow - tick >= 1)
        {
            ++tick;
            fps = frameCounter;
            frameCounter = 0;
        }

        if (!frame.empty())
        {
            //convert image to gray scale and equalize
            cvtColor(frame, graySacleFrame, CV_BGR2GRAY);
            equalizeHist(graySacleFrame, graySacleFrame);

            face_cascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));

            std::cout << "Faces detected: " << faces.size() << std::endl;
            std::cout << "Average FPS: " << fps << std::endl;

            std::string faceset = std::to_string(faces.size());

            #pragma omp parallel for
            for (int i = 0; i < int(faces.size()); i++)
            {
                rectangle(frame, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(255, 0, 255), 1, 8, 0);
                std::cout << faces[i].width << " x " << faces[i].height << std::endl;
                width = faces[i].width; height = faces[i].height;

                // select the roi
                roi.x = faces[i].x; roi.width = faces[i].width;
                roi.y = faces[i].y; roi.height = faces[i].height;

                // get the roi from orginal frame
                cropImg = frame(roi);
            }

            std::string frameset = std::to_string(fps);
            std::string wi = std::to_string(width);
            std::string he = std::to_string(height);

            cv::putText(frame, "Average FPS: " + frameset, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(frame, "Faces Detected: " + faceset, cvPoint(30, 60), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(frame, "Resolution: " + wi + " x " + he, cvPoint(30, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);

            imshow(window, frame);
        }
    }
}

void VideoCap::CannyEdgeDetector()
{
    cv::Mat edges;
    cv::Mat frame;
    const std::string window = "Capture - canny edge detection";
    double fps = 0.0;
    long int frameCounter = 0;
    int tick = 0;

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Camera opened" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    std::time_t timeBegin = std::time(0);

    while (cv::waitKey(30) != 10)
    {
        cap.read(frame);
        ++frameCounter;

        std::time_t timeNow = std::time(0) - timeBegin;
        if (timeNow - tick >= 1)
        {
            ++tick;
            fps = frameCounter;
            frameCounter = 0;
        }

        if (!frame.empty())
        {
            std::cout << "Average FPS: " << fps << std::endl;

            cvtColor(frame, edges, CV_HLS2BGR);
            GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
            Canny(edges, edges, 0, 30, 3);

            std::string frameset = std::to_string(fps);
            cv::putText(frame, "Average FPS: " + frameset, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);

            imshow(window, edges);
        }
    }
}

void VideoCap::OriginalCapturing()
{
    cv::Mat frame;
    const std::string window = "Capture - original";
    double fps = 0.0;
    long int frameCounter = 0;
    int tick = 0;

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "exit" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    std::time_t timeBegin = std::time(0);

    while (cv::waitKey(30) < 0)
    {
        cap.read(frame);
        ++frameCounter;

        std::time_t timeNow = std::time(0) - timeBegin;
        if (timeNow - tick >= 1)
        {
            ++tick;
            fps = frameCounter;
            frameCounter = 0;
        }

        if (!frame.empty())
        {
            std::cout << "Average FPS: " << fps << std::endl;
            std::string frameset = std::to_string(fps);
            cv::putText(frame, "Average FPS: " + frameset, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);

            imshow(window, frame);
        }
    }
}

void VideoCap::HandDetector()
{
    // TODO
}