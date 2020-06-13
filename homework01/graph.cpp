#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

double f(double x) {
    return sqrt(x);
}

int main() {
    int width, height;
    double x0, x1;
    std::cin >> width >> height >> x0 >> x1;

    auto step = (x1 - x0) / width;
    std::vector<double> values;
    auto currentX = x0;
    for (auto w = 0; w < width; ++w) {
        values.push_back(f(currentX));
        currentX += step;
    }

    auto min = *std::min_element(begin(values), end(values));
    auto max = *std::max_element(begin(values), end(values));

    min = (max > 0 & min > 0) ? 0 : min;
    max = (max < 0 & min < 0) ? 0 : max;

    auto scale = height / (max - min);
    auto zeroHeight = floor(-min * scale);
    auto relHeight = height;
    std::fstream outputFile;
    outputFile.open("output.txt", std::ios::out);

    for (int i = 0; i < height + 1; i++) {
        for (auto value : values) {
            value = floor((value - min) * scale);
            if (relHeight == zeroHeight)
                outputFile << '.';
            else if (value > relHeight && relHeight > zeroHeight)
                outputFile << "#";
            else if (value <= relHeight && relHeight < zeroHeight)
                outputFile << "#";
            else
                outputFile << " ";
        }

        outputFile << std::endl;
        relHeight--;
    }
}