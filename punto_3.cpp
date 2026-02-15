#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>



struct Pixel {
    double r, g, b;

    Pixel() : r(0), g(0), b(0) {}

    Pixel(double r_, double g_, double b_)
        : r(r_), g(g_), b(b_) {}
};

double distancia_euclidiana(const Pixel& p1, const Pixel& p2) {
    // TODO: Implementar
    double distancia_euclidiana(const Pixel& p1, const Pixel& p2); {

    double dr = p1.r - p2.r;
    double dg = p1.g - p2.g;
    double db = p1.b - p2.b;

    return std::sqrt(dr * dr + dg * dg + db * db);
}

}

void ejercicio3_kmeans_manual(int K = 5) {

    cv::Mat img_bgr = cv::imread("peak.jpg");
    if (img_bgr.empty()) return;

    // Redimensionar para acelerar
    cv::Mat img_small;
    cv::resize(img_bgr, img_small, cv::Size(160, 120));

    int rows = img_small.rows;
    int cols = img_small.cols;
    int total_pixels = rows * cols;

    std::cout << "Procesando "
              << total_pixels
              << " píxeles con K="
              << K
              << std::endl;

    // TODO: PASO 1 - Crear array de píxeles
    // Almacenar todos los píxeles en un vector
    std::vector<Pixel> pixeles;

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cv::Vec3b bgr = img_small.at<cv::Vec3b>(i, j);

            double b = bgr[0];
            double g = bgr[1];
            double r = bgr[2];

            pixeles.emplace_back(r, g, b);
        }
    }

    // TODO: PASO 2 - Inicializar K centroides aleatorios

    std::vector<Pixel> centroids;
    centroids.reserve(K);

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, pixeles.size() - 1);


    for (int i = 0; i < K; i++) {
        centroids.push_back(pixeles[dis(gen)]);
    }

    // TODO: PASO 3 - Array para almacenar asignaciones
    std::vector<int> labels(pixeles.size());

    for (int i = 0; i < pixeles.size(); i++) {

        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;

        for (int k = 0; k < K; k++) {

            double dist = distancia_euclidiana(pixeles[i], centroids[k]);

            if (dist < min_dist) {
                min_dist = dist;
                best_cluster = k;
            }
        }

        labels[i] = best_cluster;
    }

    // Cada píxel se asigna a un cluster [0, K-1]

    // TODO: PASO 4 - Iterar K-Means
    int max_iteraciones = 20;

    for (int iter = 0; iter < max_iteraciones; iter++) {

        std::cout << "Iteración "
                  << (iter + 1)
                  << "/"
                  << max_iteraciones
                  << std::endl;

        // PASO 4a: Asignar cada píxel al centroide más cercano
        for (int i = 0; i < pixeles.size(); i++) {

        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;

        for (int k = 0; k < K; k++) {

            double dist = distancia_euclidiana(pixeles[i], centroids[k]);

            if (dist < min_dist) {
                min_dist = dist;
                best_cluster = k;
            }
        }

        labels[i] = best_cluster;
    }

        // PASO 4b: Recalcular centroides
        // Crear arrays para sumar RGB de cada cluster
            std::vector<double> sum_r(K, 0.0);
    std::vector<double> sum_g(K, 0.0);
    std::vector<double> sum_b(K, 0.0);
    std::vector<int> count(K, 0);

    // Sumar píxeles por cluster
    for (int i = 0; i < pixeles.size(); i++) {

        int cluster = labels[i];

        sum_r[cluster] += pixeles[i].r;
        sum_g[cluster] += pixeles[i].g;
        sum_b[cluster] += pixeles[i].b;

        count[cluster]++;
    }

    // Calcular nuevo centroide (promedio)
    for (int k = 0; k < K; k++) {

        if (count[k] == 0) continue;  // evitar división por 0

        centroids[k].r = sum_r[k] / count[k];
        centroids[k].g = sum_g[k] / count[k];
        centroids[k].b = sum_b[k] / count[k];
    }
    }

    // TODO: PASO 5 - Crear imagen cuantizada
    // Reemplazar cada píxel por el color de su centroide
    cv::Mat img_quantized(rows, cols, CV_8UC3);

    int index = 0;

for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {

        int cluster = labels[index];

        Pixel c = centroids[cluster];

        // OpenCV usa BGR
        img_quantized.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(c.b);
        img_quantized.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(c.g);
        img_quantized.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(c.r);

        index++;
    }
}

    // TODO: PASO 6 - Crear paleta de colores

    int ancho_bloque = 100;
    int alto_bloque = 100;

    cv::Mat paleta(alto_bloque, K * ancho_bloque, CV_8UC3);

    for (int k = 0; k < K; k++) {

    Pixel c = centroids[k];

    cv::Vec3b color;
    color[0] = static_cast<uchar>(c.b);
    color[1] = static_cast<uchar>(c.g);
    color[2] = static_cast<uchar>(c.r);

    for (int y = 0; y < alto_bloque; y++) {
        for (int x = k * ancho_bloque; x < (k + 1) * ancho_bloque; x++) {
            paleta.at<cv::Vec3b>(y, x) = color;
        }
    }
}


    cv::imshow("Original", img_small);
    cv::imshow("K-Means Manual K=" + std::to_string(K), img_quantized);
    cv::imshow("Paleta", paleta);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
