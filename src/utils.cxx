#include "utils.h"
#include <random>

int get_index(int x, int y, int width) { return x + width * y; }

void generate_noise(std::vector<double> &noise, int width, int height) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            noise[get_index(x, y, width)] = dist(mt);
        }
    }
}

double smooth_noise(double x, double y, int width, int height,
                    std::vector<double> &noise) {

    // Get fraction part of X and Y
    double fraction_x = x - int(x);
    double fraction_y = y - int(y);

    // Wrap around
    int x1 = (int(x) + width) % width;
    int y1 = (int(y) + height) % height;

    // Get Neighbors
    int x2 = (x1 + width - 1) % width;
    int y2 = (y1 + height - 1) % height;

    // Smooth the noise
    double value = 0.0;
    value += fraction_x * fraction_y * noise[get_index(x1, y1, width)];
    value += (1 - fraction_x) * fraction_y * noise[get_index(x2, y1, width)];
    value += fraction_x * (1 - fraction_y) * noise[get_index(x1, y2, width)];
    value +=
        (1 - fraction_x) * (1 - fraction_y) * noise[get_index(x2, y2, width)];

    return value;
}

double turbulence(double x, double y, int width, int height, double size,
                  std::vector<double> &noise) {

    double value = 0.0;
    double initial_size = size;

    while (size >= 1) {
        value += smooth_noise(x / size, y / size, width, height, noise) * size;
        size /= 2.0;
    }

    return (128.0 * value / initial_size);
}
