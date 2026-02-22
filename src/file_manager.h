#pragma once

#include "structs.h"
#include <string>
#include <vector>

static bool start_with_case_insensitive(std::string line, std::string to_match);

std::tuple<int, int> get_width_and_height(const std::string line);

static std::tuple<int, int, int> get_color(const std::string line);

void save_image(std::vector<std::tuple<float, float, float>> &image, int width,
                int height, std::string filename);

void save_image(Image &image);

void read_image(std::vector<std::tuple<float, float, float>> &image, int &width,
                int &height, std::string filename);

void read_image(Image &image);
