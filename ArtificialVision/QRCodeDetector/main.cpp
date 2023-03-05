// detect and decode QR code via video capture
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct Line
{
    cv::Point2f initialPoint;
    cv::Point2f endPoint;
};

void Display(cv::Mat& image, cv::Mat& box, std::string title)
{
    Line topLine   { box.ptr<cv::Point2f>(0)[0], box.ptr<cv::Point2f>(0)[1] };
    cv::line(image, topLine.initialPoint, topLine.endPoint, cv::Scalar(255, 0, 0), 3);

    Line rightLine { box.ptr<cv::Point2f>(0)[1], box.ptr<cv::Point2f>(0)[2] };
    cv::line(image, rightLine.initialPoint, rightLine.endPoint, cv::Scalar(255, 0, 0), 3);

    Line leftLine  { box.ptr<cv::Point2f>(0)[2], box.ptr<cv::Point2f>(0)[3] };
    cv::line(image, leftLine.initialPoint, leftLine.endPoint, cv::Scalar(255, 0, 0), 3);

    Line bottomLine{ box.ptr<cv::Point2f>(0)[3], box.ptr<cv::Point2f>(0)[0] };
    cv::line(image, bottomLine.initialPoint, bottomLine.endPoint, cv::Scalar(255, 0, 0), 3);

    cv::imshow(title, image);
}

void PrintContent(std::string content)
{
    std::cout << content << std::endl;
}

int main()
{
    cv::VideoCapture cap(0);
    cv::Mat frame;
    auto qrDecoder = cv::QRCodeDetector();
    cv::Mat box;

    while (true)
    {
        cap >> frame;

        if (qrDecoder.detect(frame, box))
        {
            auto content = qrDecoder.decode(frame, box);
            PrintContent(content);
            Display(frame, box, "syro");
            cv::waitKey(16);
        }
        else
        {
            cv::imshow("syro", frame);
            cv::waitKey(16);
        }
        
    }
    return 0;
}