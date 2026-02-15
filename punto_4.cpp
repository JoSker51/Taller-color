#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>


void ejercicio4_gray_world() {

    cv::Mat img_bgr = cv::imread("peak.jpg");
    if (img_bgr.empty()) return;

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;
    int total_pixels = rows * cols;

    // TODO: PASO 1 - Calcular suma de cada canal
    double sum_R = 0.0;
    double sum_G = 0.0;
    double sum_B = 0.0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b pixel = img_bgr.at<cv::Vec3b>(i, j);

            sum_B += pixel[0];
            sum_G += pixel[1];
            sum_R += pixel[2];
        }
    }

    // TODO: PASO 2 - Calcular promedios

    double avg_R = sum_R / total_pixels;
    double avg_G = sum_G / total_pixels;
    double avg_B = sum_B / total_pixels;

    // TODO: PASO 3 - Calcular promedio gris

    double gray_avg = (avg_R + avg_G + avg_B)/3;


    // TODO: PASO 4 - Calcular factores de escala

    double scale_R = gray_avg/avg_R;
    double scale_G = gray_avg/avg_G;
    double scale_B = gray_avg/avg_B;

    // TODO: PASO 5 - Crear imagen corregida

    cv::Mat img_resultado(rows, cols, CV_8UC3);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b pixel = img_bgr.at<cv::Vec3b>(i, j);

            double new_R = std::min(pixel[2] * scale_R, 255.0);
            double new_G = std::min(pixel[1] * scale_G, 255.0);
            double new_B = std::min(pixel[0] * scale_B, 255.0);

            img_resultado.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(new_B);
            img_resultado.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(new_G);
            img_resultado.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(new_R);
        }
    }

    cv::imshow("Original", img_bgr);
    cv::imshow("Gray World", img_resultado);

    cv::waitKey(0);
    cv::destroyAllWindows();
}