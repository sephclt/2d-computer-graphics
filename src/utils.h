#pragma once

#include <vector>
#include "draw.h"
#include "structs.h"

int get_index(int x, int y, int width);

void generate_noise(std::vector<double> &noise, int width, int height);

void generate_noise(ImageTexture &image_texture);

double smooth_noise(double x, double y, int width, int height,
                    std::vector<double> &noise);

double turbulence(double x, double y, int width, int height, double size,
                  std::vector<double> &noise);

SampleImageType parseSampleImageTypeString(std::string type);

SampleImageType parseSampleImageTypeString(char *type);
