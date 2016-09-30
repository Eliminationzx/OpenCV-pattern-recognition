#include "FaceRec.h"

void FaceRecognition::DBRead(const std::string& fileName, char separator)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in);

    if (!file)
    {
        CV_Error(CV_StsBadArg, "No valid inout file!");
        return;
    }

    std::string line, path, label;
    while (std::getline(file, line))
    {
        std::stringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, label);

        if (!path.empty() && !label.empty())
        {
            _img.push_back(cv::imread(path, 0));
            _labels.push_back(atoi(label.c_str()));
        }
    }
}

void FaceRecognition::EigenFaceTrainer(const std::string fileName)
{
    try
    {
        DBRead(fileName);
        std::cout << "Size of the images is " << _img.size() << std::endl;
        std::cout << "Size of the labels is " << _labels.size() << std::endl;
        std::cout << "Training begins...." << std::endl;
    }
    catch (cv::Exception& e)
    {
        std::cerr << "Error opening the file " << e.msg << std::endl;
        exit(EXIT_FAILURE);
    }

    cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
    model->train(_img, _labels);
    model->save("/");

    std::cout << "Training finished...." << std::endl;
    cv::waitKey(10000);
}

void FaceRecognition::FisherFaceTrainer(const std::string fileName)
{
    try
    {
        DBRead(fileName);
        std::cout << "Size of the images is " << _img.size() << std::endl;
        std::cout << "Size of the labels is " << _labels.size() << std::endl;
        std::cout << "Training begins...." << std::endl;
    }
    catch (cv::Exception& e)
    {
        std::cerr << "Error opening the file " << e.msg << std::endl;
        exit(EXIT_FAILURE);
    }

    cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    model->train(_img, _labels);

    int height = _img[0].rows;

    model->save("/");

    std::cout << "Training finished...." << std::endl;

    cv::Mat eigenvalues = model->getMat("eigenvalues");
    cv::Mat W = model->getMat("eigenvectors");
    cv::Mat mean = model->getMat("mean");

    cv::waitKey(10000);
}

void FaceRecognition::LBPHFaceTrainer(const std::string fileName)
{
    try
    {
        DBRead(fileName);
        std::cout << "Size of the images is " << _img.size() << std::endl;
        std::cout << "Size of the labels is " << _labels.size() << std::endl;
        std::cout << "Training begins...." << std::endl;
    }
    catch (cv::Exception& e)
    {
        std::cerr << "Error opening the file " << e.msg << std::endl;
        exit(EXIT_FAILURE);
    }

    cv::Ptr<cv::FaceRecognizer> model = cv::createLBPHFaceRecognizer();
    model->train(_img, _labels);
    model->save("/");

    std::cout << "Training finished...." << std::endl;
    cv::waitKey(10000);
}

void FaceRecognition::Execute(const std::string fileName, const std::string grayScale)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame;
    cv::Mat graySacleFrame;
    cv::Mat original;

    std::cout << "Start recognizing..." << std::endl;

    // load pre-trained data sets
    cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    model->load(fileName);

    cv::Mat testSample = cv::imread(grayScale, 0);

    int img_width = testSample.cols;
    int img_height = testSample.rows;

    std::string classifier = OPENCV_CASCADE;

    cv::CascadeClassifier face_cascade;
    const std::string window = "Capture - face detection";

    if (!face_cascade.load(classifier))
    {
        std::cout << "Error loading file" << std::endl;
        return;
    }

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Exit" << std::endl;
        return;
    }

    cv::namedWindow(window, 1);
    long int frameCounter = 0;

    while (cv::waitKey(30) < 0)
    {
        cap >> frame;
        ++frameCounter;

        if (!frame.empty())
        {
            original = frame.clone(); // clone from original frame

            cvtColor(original, graySacleFrame, CV_BGR2GRAY); // convert image to gray scale and equalize

            face_cascade.detectMultiScale(graySacleFrame, faces, 1.1, 3, 0, cv::Size(90, 90)); // detect face in gray image

            // Number of faces detected
            std::cout << faces.size() << "Faces detected" << std::endl;

            int width = 0, height = 0;

            std::string Pname = ""; // person name

            for (int i = 0; i < int(faces.size()); i++)
            {
                cv::Rect face_i = faces[i]; // region of interest
                cv::Mat face = graySacleFrame(face_i);

                // Resizing the cropped image to suit to database image sizes
                cv::Mat face_resized;
                cv::resize(face, face_resized, cv::Size(img_width, img_height), 1.0, 1.0, cv::INTER_CUBIC);

                // Recognizing what faces detected
                int label = -1; double confidence = 0;
                model->predict(face_resized, label, confidence);

                std::cout << " confidencde " << confidence << std::endl;

                // Drawing green rectagle in recognize face
                rectangle(original, face_i, GREEN, 1);

                /*if (label == 40)
                {
                Pname = "Timur";
                }
                else*/
                {
                    Pname = "unknown";
                }


                int pos_x = std::max(face_i.tl().x - 10, 0);
                int pos_y = std::max(face_i.tl().y - 10, 0);

                // Name the person who is in the image
                putText(original, "Detected", cv::Point(pos_x, pos_y), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, GREEN, 1);

            }

            putText(original, "Frames: " + frameCounter, cv::Point(30, 60), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, GREEN, 1);
            putText(original, "Person: " + Pname, cv::Point(30, 90), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, GREEN, 1);

            imshow(window, original);
        }
    }
}