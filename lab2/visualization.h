#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "map.h"

#define SIZE 100

cv::Mat InitMat(int rows, int cols);
void Rectangle(cv::Mat img, int row, int col, const cv::Scalar &color);
void Path(cv::Mat img, const std::vector<Location> &path);
void Circle(cv::Mat img, Location l, const cv::Scalar &color);
void Grid(cv::Mat img);
