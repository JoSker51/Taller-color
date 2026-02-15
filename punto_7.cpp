#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>


void ejercicio7_vignette(double k = 0.4) {

    cv::Mat img_bgr = cv::imread("peak.jpg");
    cv::Mat img_resultado = img_bgr.clone();

    if (img_bgr.empty()) return;

    int rows = img_bgr.rows;
    int cols = img_bgr.cols;

    // TODO: PASO 1 - Calcular centro de la imagen
    
    double cx = cols/2 ;
    double cy = rows/2 ;

    // TODO: PASO 2 - Calcular distancia máxima (a la esquina)
    double d_max = std::sqrt(cx * cx + cy * cy);


    // TODO: PASO 3 - Aplicar corrección píxel por píxel
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            
            double d = std::sqrt((j - cx)*(j - cx) + (i - cy)*(i - cy));

            
            double d_norm = d / d_max;

            
            double f = 1.0 / (1.0 - k * d_norm * d_norm);

            
            cv::Vec3b pixel = img_bgr.at<cv::Vec3b>(i, j);

            for (int c = 0; c < 3; c++) {
                double nuevo_valor = pixel[c] * f;

                if (nuevo_valor > 255.0)
                    nuevo_valor = 255.0;

                img_resultado.at<cv::Vec3b>(i, j)[c] = static_cast<uchar>(nuevo_valor);
            }
        }
    }

    cv::imshow("Original", img_bgr);
    cv::imshow("Viñeteo Corregido k=" + std::to_string(k), img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
