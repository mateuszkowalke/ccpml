#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

enum IrisClasses { IrisSetosa, IrisVersicolor, IrisVirginica, IrisUnknown };

std::vector<std::vector<float>> readIrisDataset() {
  std::ifstream file("data/iris.data");
  std::string line;
  std::vector<std::vector<float>> dataset;
  std::vector<float> tempSepalLen;
  std::vector<float> tempSepalWid;
  std::vector<float> tempPetalLen;
  std::vector<float> tempPetalWid;
  std::vector<float> tempIrisClass;

  float sepalLenF, sepalWidF, petalLenF, petalWidF;
  float irisClassF;

  std::string tempString;
  int count = 0;

  if (file.is_open()) {
    std::cout << "File opened successfuly." << std::endl;
    while (std::getline(file, line)) {
      std::replace(line.begin(), line.end(), '-', '_');
      std::replace(line.begin(), line.end(), ',', ' ');

      std::istringstream iss(line);
      count++;

      iss >> sepalLenF >> sepalWidF >> petalLenF >> petalWidF >> tempString;
      tempSepalLen.push_back(sepalLenF);
      tempSepalWid.push_back(sepalWidF);
      tempPetalLen.push_back(petalLenF);
      tempPetalWid.push_back(petalWidF);

      if (tempString.compare("Iris_setosa") == 0) {
        irisClassF = IrisSetosa;
      } else if (tempString.compare("Iris_versicolor") == 0) {
        irisClassF = IrisVersicolor;
      } else if (tempString.compare("Iris_virginica") == 0) {
        irisClassF = IrisVirginica;
      } else {
        irisClassF = IrisUnknown;
      }
      tempIrisClass.push_back(irisClassF);
    }

    dataset.push_back(tempSepalLen);
    dataset.push_back(tempSepalWid);
    dataset.push_back(tempPetalLen);
    dataset.push_back(tempPetalWid);
    dataset.push_back(tempIrisClass);

  } else {
    std::cout << "Unable to open file." << std::endl;
  }

  return dataset;
}

int main() {
  std::vector<std::vector<float>> dataset = readIrisDataset();
  plt::plot(dataset[0], {{"label", "sepal_length"}});
  plt::plot(dataset[1], {{"label", "sepal_width"}});
  plt::plot(dataset[2], {{"label", "petal_length"}});
  plt::plot(dataset[3], {{"label", "petal_width"}});
  plt::title("Standard usage");
  plt::legend();
  plt::show();
}

