#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

void ejercicio1_rgb_a_hsv() {
    
    cv::Mat img_bgr = cv::imread("peak.jpg");

    if (img_bgr.empty()) {
        std::cout << "Error: No se pudo cargar la imagen" << std::endl;
        return;
    }
    int rows = img_bgr.rows;

    int cols = img_bgr.cols;

    cv::Mat img_hsv(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            cv::Vec3b pixel_bgr = img_bgr.at<cv::Vec3b>(i, j);

             float B = pixel_bgr[0] / 255.0;

             float G = pixel_bgr[1] / 255.0;

             float R = pixel_bgr[2] / 255.0;
// Calcular Cmax, Cmin, Delta

             double Cmax = std:: max(B, std::max(G,R));

             double Cmin = std:: min(B, std::min(G,R));

             double Delta = Cmax-Cmin;

             float H = 0.0;
// Calcular Hue (H)
            if (Delta == 0){
                H = 0.0;
                
            }
            else if (Cmax == R){
                H = 60.0 * std::fmod(((G-B)/Delta),6);
            }
            else if (Cmax == G){
                H = 60.0 * ((B-R)/Delta + 2);
            }
            else if(Cmax == B){
                H = 60.0 * ((R-G)/Delta + 4);

            }

            double S;
           
// Calcular Saturation (S)
            if (Cmax == 0){
                S = 0;
            }else{
                S = Delta/Cmax;
            }
// Calcular Value (V)
            double V = Cmax;
// Asignar valores HSV al píxel=
            img_hsv.at<cv::Vec3b>(i, j)[0] = static_cast<unsigned char>(H / 2.0);
            img_hsv.at<cv::Vec3b>(i, j)[1] = static_cast<unsigned char>(S * 255.0);
            img_hsv.at<cv::Vec3b>(i, j)[2] = static_cast<unsigned char>(V * 255.0);
        }
    }

    cv::imshow("Original BGR", img_bgr);

    cv::imshow("HSV (Manual)", img_hsv);

    cv::waitKey(0);

    cv::destroyAllWindows();
}