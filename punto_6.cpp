#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>

void ejercicio6_gamma(double gamma = 1.5) {

    cv::Mat img_bgr = cv::imread("peak.jpg");
    if (img_bgr.empty()) return;

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;

    // TODO: PASO 1 - Crear tabla de lookup (para eficiencia)
    // Pre-calcular la transformación para todos los valores 0-255
    std::vector<uchar> LUT(256);

for (int i = 0; i < 256; i++) {

    double normalized = static_cast<double>(i) / 255.0;
    double corrected = std::pow(normalized, gamma);
    int value = static_cast<int>(255.0 * corrected);


    LUT[i] = static_cast<uchar>(value);
}

    // TODO: PASO 2 - Aplicar transformación a cada píxel
cv::Mat img_resultado(rows, cols, CV_8UC3);

for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {

        cv::Vec3b pixel = img_bgr.at<cv::Vec3b>(y, x);

        pixel[0] = LUT[pixel[0]];  // B
        pixel[1] = LUT[pixel[1]];  // G
        pixel[2] = LUT[pixel[2]];  // R

        img_resultado.at<cv::Vec3b>(y, x) = pixel;
    }
}

    cv::imshow("Original", img_bgr);
    cv::imshow("Gamma = " + std::to_string(gamma), img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
