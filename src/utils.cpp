#include "utils.h"
#include <iostream>
#include <opencv2/core.hpp>

void setPixels(cv::Mat &img1, cv::Mat &img2, cv::Mat &img3, int y, int x,
               char ch) {
  int ascii =static_cast<unsigned char>(ch); 
  for (int i = 0; i < 8; i++) {
    int bit = (ascii >> (7 - i)) & 1;
    int pixel_x = x + i;
    if (y < img1.rows && pixel_x < img1.cols) {
      img1.at<uchar>(y, pixel_x) = bit ? 255 : 0;
      img2.at<uchar>(y, pixel_x) = bit ? 255 : 0;
      img3.at<uchar>(y, pixel_x) = bit ? 255 : 0;
    } else {
      std::cerr << "Warning: Pixel (" << y << ", " << pixel_x
                << ") is out of bounds!" << std::endl;
    }
  }
}

char getCharFromPixels(const cv::Mat &img1, const cv::Mat &img2,
                       const cv::Mat &img3, int y, int x) {
  int ascii = 0;
  for (int i = 0; i < 8; i++) {
    int pixel_x = x + i;
    if (y < img1.rows && pixel_x < img1.cols) {
      int bit1 = img1.at<uchar>(y, pixel_x) > 127 ? 1 : 0;
      int bit2 = img2.at<uchar>(y, pixel_x) > 127 ? 1 : 0;
      int bit3 = img3.at<uchar>(y, pixel_x) > 127 ? 1 : 0;
      int combined_bit = (bit1 & bit2) | (bit1 & bit3) | (bit2 & bit3);
      ascii |= (combined_bit << (7 - i)); 
    } else {
      std::cerr << "Warning: Pixel (" << y << ", " << pixel_x
                << ") is out of bounds when reading!" << std::endl;
    }
  }
  return static_cast<char>(ascii);
}
