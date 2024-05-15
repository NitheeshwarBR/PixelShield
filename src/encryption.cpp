#include "encryption.h"
#include "utils.h"
#include <fstream>
#include <opencv2/opencv.hpp>

void encryptText(const std::string &inputFilename,
                 const std::string &outputBase) {
  std::ifstream file(inputFilename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << inputFilename << std::endl;
    return;
  }

  std::string line;
  int max_width = 0;
  std::vector<std::string> lines;
  while (getline(file, line)) {
    lines.push_back(line);
    max_width = std::max(max_width, static_cast<int>(line.size()));
  }
  file.close();

  int height = lines.size();
  int width = max_width * 8;
  cv::Mat image1(height, width, CV_8UC1, cv::Scalar(255));
  cv::Mat image2(height, width, CV_8UC1, cv::Scalar(255));
  cv::Mat image3(height, width, CV_8UC1, cv::Scalar(255));

  for (int y = 0; y < height; ++y) {
    for (size_t x = 0; x < lines[y].size(); ++x) {
      setPixels(image1, image2, image3, y, x * 8, lines[y][x]);
    }
  }
  cv::imwrite(outputBase + "1.png", image1);
  cv::imwrite(outputBase + "2.png", image2);
  cv::imwrite(outputBase + "3.png", image3);
}
