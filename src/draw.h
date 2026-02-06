#pragma once

#include <tuple>
#include <vector>

void first_draw(std::vector<std::tuple<float, float, float>> &image, int width,
                int height);

void walker_draw(std::vector<std::tuple<float, float, float>> &image1,
                 std::vector<std::tuple<float, float, float>> &image2,
                 int width, int height);

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width,
                 int height, std::tuple<float, float, float> &color);

static void update_x_and_y(int r, std::tuple<int, int> &walk1,
                           std::tuple<int, int> &walk2, int width, int height);

void draw_or(std::vector<std::tuple<float, float, float>> &image, int width,
             int height);

void draw_and(std::vector<std::tuple<float, float, float>> &image, int width,
              int height);

void draw_xor(std::vector<std::tuple<float, float, float>> &image, int width,
              int height);

void generate_cloud(std::vector<std::tuple<float, float, float>> &image,
                    int width, int height, std::vector<double> &noise);

void generate_marble(std::vector<std::tuple<float, float, float>> &image,
                     int width, int height, std::vector<double> &noise);

void generate_wood(std::vector<std::tuple<float, float, float>> &image,
                   int width, int height, std::vector<double> &noise);
