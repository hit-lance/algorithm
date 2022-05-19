#include "visualization.h"

cv::Mat InitMat(int rows, int cols) { return cv::Mat(rows * SIZE, cols * SIZE, CV_8UC3, cv::Scalar(255, 255, 255)); }

void Rectangle(cv::Mat img, int row, int col, const cv::Scalar &color) {
    cv::rectangle(img, {col * SIZE, row * SIZE}, {(col + 1) * SIZE, (row + 1) * SIZE}, color, cv::FILLED);
}

void Path(cv::Mat img, const std::vector<Location> &path) {
    for (size_t i = 1; i < path.size(); ++i) {
        cv::line(img, {path[i - 1].second * SIZE + SIZE / 2, path[i - 1].first * SIZE + SIZE / 2},
                 {path[i].second * SIZE + SIZE / 2, path[i].first * SIZE + SIZE / 2}, {0, 128, 255}, 8, 16);
    }
}

void Circle(cv::Mat img, Location l, const cv::Scalar &color) {
    cv::circle(img, {l.second * SIZE + SIZE / 2, l.first * SIZE + SIZE / 2}, SIZE / 8, color, cv::FILLED);
}

void Grid(cv::Mat img) {
    int rows = img.rows, cols = img.cols;
    for (int i = 0; i <= rows; i += SIZE) {
        cv::line(img, {0, i}, {cols, i}, {0, 0, 0}, 2);
    }
    for (int i = 0; i <= cols; i += SIZE) {
        cv::line(img, {i, 0}, {i, rows}, {0, 0, 0}, 2);
    }
}
