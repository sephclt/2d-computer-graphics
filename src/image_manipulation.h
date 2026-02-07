#pragma once

#include "structs.h"

enum DarkenValue { DOUBLE, HALF };

enum BrightenType { ADD, MULTIPLY };

void negative_image(Image &image);

void darken_image(Image &image, DarkenValue value);

void brighten_image(Image &image, BrightenType type, float value);

void brighten_image_add(Image &image, float value);

void brighten_image_multiply(Image &image, float value);

void subtract_image(Image &image, float value);
