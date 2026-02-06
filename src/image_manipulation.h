#pragma once

#include "structs.h"

enum DarkenValue { DOUBLE, HALF };

void negative_image(Image &image);

void darken_image(Image &image, DarkenValue value);
