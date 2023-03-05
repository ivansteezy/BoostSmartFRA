// car plates detection from an image
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// this basically means how far is the camera from the car
const double AREA_COUNTOUR = 5000;
int main()
{
    cv::Mat image;
    cv::Mat grayImage;
    cv::Mat canny;
    std::vector<std::vector<cv::Point>> contours;

    image = cv::imread("auto001.jpg");
    // image = cv::imread("placa2.jpg");

    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    
    cv::Canny(grayImage, canny, 150, 200);

    cv::Mat improved;
    cv::dilate(canny, improved, cv::Mat());

    cv::findContours(improved, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 2);
    
    for (auto contour : contours)
    {
        auto area = cv::contourArea(contour);
        auto rect = cv::boundingRect(contour);
        auto epsilon = 0.09 * cv::arcLength(contour, true);

        std::vector<cv::Point> aprox;
        cv::approxPolyDP(cv::Mat(contour), aprox, epsilon, true);

        if ((aprox.size() == 4) && (area > AREA_COUNTOUR))
        {
            // std::cout << "AREA: " << area << "\n";
            // std::vector<std::vector<cv::Point>> c;
            // c.push_back(contour);

            // cv::drawContours(image, c, 0, cv::Scalar(255, 0, 0), 2);
            auto aspectRatio = float(rect.width) / float(rect.height);

            if (aspectRatio > 2.4)
            {
                std::vector<std::vector<cv::Point>> c;
                c.push_back(contour);
                cv::drawContours(image, c, 0, cv::Scalar(255, 0, 0), 4);
                cv::Rect rectSection(rect.x, rect.y, rect.width, rect.height);
                auto placa = cv::Mat(grayImage(rectSection));
                cv::imshow("placa", placa);
            }
        }
    }

    cv::imshow("Image", image);
    // cv::imshow("Canny", canny);
    // cv::imshow("Improved", improved);
    cv::waitKey(0);
}