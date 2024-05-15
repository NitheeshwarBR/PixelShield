#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core/mat.hpp>

void setPixels(cv::Mat &img1, cv::Mat &img2, cv::Mat &img3, int y, int x,
               char ch);
char getCharFromPixels(const cv::Mat &img1, const cv::Mat &img2,
                       const cv::Mat &img3, int y, int x);

#endif // UTILS_H
