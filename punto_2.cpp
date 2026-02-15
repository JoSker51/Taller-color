#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

void ejercicio2_modificar_saturacion() {

    cv::Mat img_bgr = cv::imread("peak.jpg");


    int rows = img_bgr.rows;
    int cols = img_bgr.cols;


    //prueba
    
    std::cout << "Rows: " << rows << " Cols: " << cols << std::endl;

    //fin de prueba



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

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cv::Vec3b pixel_hsv = img_hsv.at<cv::Vec3b>(i, j);

            // PASO 1: Obtener valores H, S, V
            int H = pixel_hsv[0];
            int S = pixel_hsv[1];
            int V = pixel_hsv[2];

            // PASO 2: Multiplicar S por 1.5 (sin exceder 255)
            S = static_cast<int>(S * 1.5);

            if (S > 255) {
                S = 255;
            }

            // PASO 3: Asignar nuevos valores
            img_hsv.at<cv::Vec3b>(i, j)[0] = H;
            img_hsv.at<cv::Vec3b>(i, j)[1] = S;
            img_hsv.at<cv::Vec3b>(i, j)[2] = V;

        }
    }

    cv::Mat img_resultado(rows, cols, CV_8UC3);

    for(int i=0; i < rows; i++){
        for(int j= 0; j< cols; j++) {

            cv::Vec3b pixel_hsv = img_hsv.at<cv::Vec3b>(i, j);

            //normalizacion de valores
            float H = pixel_hsv[0] * 2.0f;
            float S = pixel_hsv[1] / 255.0f;
            float V = pixel_hsv[2] / 255.0f;


            float C = V * S;
            float X = C * (1 - std::fabs(std::fmod(H / 60.0f, 2.0f) - 1));
            float m = V - C;

            // segun el rango de H

            float R1, G1, B1;

            if (H >= 0 && H < 60) {
                R1 = C; G1 = X; B1 = 0;
            }
            else if (H < 120) {
                R1 = X; G1 = C; B1 = 0;
            }
            else if (H < 180) {
                R1 = 0; G1 = C; B1 = X;
            }
            else if (H < 240) {
                R1 = 0; G1 = X; B1 = C;
            }
            else if (H < 300) {
                R1 = X; G1 = 0; B1 = C;
            }
            else {
                R1 = C; G1 = 0; B1 = X;
            }

            unsigned char R = static_cast<unsigned char>((R1 + m) * 255.0f);
            unsigned char G = static_cast<unsigned char>((G1 + m) * 255.0f);
            unsigned char B = static_cast<unsigned char>((B1 + m) * 255.0f);

            img_resultado.at<cv::Vec3b>(i, j)[0] = B;
            img_resultado.at<cv::Vec3b>(i, j)[1] = G;
            img_resultado.at<cv::Vec3b>(i, j)[2] = R;
        }
    }
    

    cv::imshow("Original", img_bgr);
    cv::imshow("Saturación Aumentada", img_resultado);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
