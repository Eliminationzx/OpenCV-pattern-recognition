#include "VideoCap.h"

void VideoCap::FaceDetector()
{
    cv::CascadeClassifier face_cascade;
    const std::string window = "Capture - face detection";
    const std::string classifier = OPENCV_FACE;

    long frames = 0;
    int width = 0, height = 0;

    std::vector<cv::Rect> faces;
    cv::Mat frame;
    cv::Mat graySacleFrame;
    cv::Mat cropImg;

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

    while (true)
    {
        cap >> frame;
        ++frames;

        if (!frame.empty())
        {
            //convert image to gray scale and equalize
            cvtColor(frame, graySacleFrame, CV_BGR2GRAY);
            equalizeHist(graySacleFrame, graySacleFrame);

            face_cascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));

            std::cout << faces.size() << "Faces detected" << std::endl;
            std::string frameset = std::to_string(frames);
            std::string faceset = std::to_string(faces.size());

            cv::Rect roi;

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

            std::string wi = std::to_string(width);
            std::string he = std::to_string(height);

            cv::putText(frame, "Frames: " + frameset, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(frame, "Faces Detected: " + faceset, cvPoint(30, 60), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(frame, "Resolution " + wi + " x " + he, cvPoint(30, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);

            imshow(window, frame);
        }
        if (cv::waitKey(30) >= 0) break;
    }
}

void VideoCap::CannyEdgeDetector()
{
    cv::Mat edges;
    cv::Mat frame;
    const std::string window = "Capture - canny edge detection";

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Camera opened" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    while (true)
    {
        cap >> frame; // get a new frame from camera
        if (!frame.empty()) 
        {
            cvtColor(frame, edges, CV_HLS2BGR);
            GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
            Canny(edges, edges, 0, 30, 3);

            imshow(window, edges);
        }
        if (cv::waitKey(30) == 10) break;
    }
}

void VideoCap::OriginalCapturing()
{
    const std::string window = "Capture - original";

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "exit" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);

    while (true)
    {
        // Reads each frame and assign to mat
        cv::Mat frame;
        cap.read(frame);

        if (!frame.empty()) imshow(window, frame);
        if (cv::waitKey(30) >= 0) break;
    }
}

void VideoCap::HandDetector()
{
    // TODO
}