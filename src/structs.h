#pragma once

#include <string>
#include <tuple>
#include <vector>

struct Image {
    std::string filename;
    std::vector<std::tuple<float, float, float>> image;
    int width;
    int height;
};
