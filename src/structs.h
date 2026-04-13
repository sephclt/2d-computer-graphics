#pragma once

#include <string>
#include <tuple>
#include <vector>

struct Image {
    std::string filename;
    int width;
    int height;
    std::vector<std::tuple<float, float, float>> image;
};

struct ImageTexture : Image {
    std::vector<double> noise;
    std::tuple<float, float, float> color;
};
