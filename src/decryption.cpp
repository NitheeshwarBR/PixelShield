#include "decryption.h"
#include "utils.h"
#include <fstream>
#include <opencv2/opencv.hpp>

void decryptImages(const std::string &inputBase,
                   const std::string &outputFilename) {
  // Load images
  cv::Mat image1 = cv::imread(inputBase + "1.png", cv::IMREAD_GRAYSCALE);
  cv::Mat image2 = cv::imread(inputBase + "2.png", cv::IMREAD_GRAYSCALE);
  cv::Mat image3 = cv::imread(inputBase + "3.png", cv::IMREAD_GRAYSCALE);

  if (image1.empty() || image2.empty() || image3.empty()) {
    std::cerr << "Error: Unable to open the images!" << std::endl;
    return;
  }

  std::ofstream outfile(outputFilename);
  if (!outfile.is_open()) {
    std::cerr << "Error: Unable to open the output file!" << std::endl;
    return;
  }

  // Assuming each row of pixels corresponds to a line of text
  for (int y = 0; y < image1.rows; ++y) {
    for (int x = 0; x < image1.cols; x += 8) {
      char ch = getCharFromPixels(image1, image2, image3, y, x);
      if (ch >= 32 && ch <= 126) { // Check if it's a printable ASCII character
        outfile << ch;
      }
    }
    outfile << '\n'; // New line for each row
  }

  outfile.close();
}
