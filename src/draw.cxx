#include "draw.h"

void first_draw(std::vector<std::tuple<float, float, float>> &image, int width,
                int height) {

    std::tuple<float, float, float> color;
    int ctr = 0;

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            float r = float(x) / float(width);
            float g = float(y) / float(height);
            float b = 0.2;
            color = std::make_tuple(r, g, b);
            image[ctr] = color;
            ctr++;
        }
    }
}

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width,
                 int height, std::tuple<float, float, float> &color) {

    for (int y = height; y > height; --y) {
        for (int x = 0; x <= width; ++x) {
            image[x + width * height] = color;
        }
    }
}
