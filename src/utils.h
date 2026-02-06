#pragma once

#include <vector>

int get_index(int x, int y, int width);

void generate_noise(std::vector<double> &noise, int width, int height);

double smooth_noise(double x, double y, int width, int height,
                    std::vector<double> &noise);

double turbulence(double x, double y, int width, int height, double size,
                  std::vector<double> &noise);
