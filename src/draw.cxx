#include "draw.h"
#include "utils.h"
#include <random>
#include <tuple>

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

void walker_draw(std::vector<std::tuple<float, float, float>> &image1,
                 std::vector<std::tuple<float, float, float>> &image2,
                 int width, int height) {

    std::tuple<float, float, float> color;
    int x1 = width / 2;
    int y1 = height / 2;
    int x2 = width / 2;
    int y2 = height / 2;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 3);

    std::tuple<int, int> walk1 = std::make_tuple(x1, y1);
    std::tuple<int, int> walk2 = std::make_tuple(x2, y2);

    int r = 0;
    for (int i = 0; i < 100000; ++i) {
        r = dist(mt);
        update_x_and_y(r, walk1, walk2, width, height);
        color =
            image1[get_index(std::get<0>(walk1), std::get<1>(walk1), width)];
        image2[get_index(std::get<0>(walk1), std::get<1>(walk1), width)] =
            color;
        color =
            image1[get_index(std::get<0>(walk2), std::get<1>(walk2), width)];
        image2[get_index(std::get<0>(walk2), std::get<1>(walk2), width)] =
            color;
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

void draw_or(std::vector<std::tuple<float, float, float>> &image, int width,
             int height) {

    std::tuple<float, float, float> color;
    int c = 0;

    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < width; ++x) {
            c = x | y;
            color = std::make_tuple(float(c / 255.0f), float(c / 255.0f),
                                    float(c / 255.0f));
            image[get_index(x, y, width)] = color;
        }
    }
}

void draw_and(std::vector<std::tuple<float, float, float>> &image, int width,
              int height) {

    std::tuple<float, float, float> color;
    int c = 0;

    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < width; ++x) {
            c = x & y;
            color = std::make_tuple(float(c / 255.0f), float(c / 255.0f),
                                    float(c / 255.0f));
            image[get_index(x, y, width)] = color;
        }
    }
}

void draw_xor(std::vector<std::tuple<float, float, float>> &image, int width,
              int height) {

    std::tuple<float, float, float> color;
    int c = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            c = x ^ y;
            color = std::make_tuple(float(c / 255.0f), float(c / 255.0f),
                                    float(c / 255.0f));
            image[get_index(x, y, width)] = color;
        }
    }
}

void generate_cloud(std::vector<std::tuple<float, float, float>> &image,
                    int width, int height, std::vector<double> &noise) {

    std::tuple<float, float, float> color;
    int c = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            c = int(turbulence(double(x), double(y), width, height, 64, noise));
            color = std::make_tuple(float(c / 255.0f), float(c / 255.0f),
                                    float(c / 255.0f));
            image[get_index(x, y, width)] = color;
        }
    }
}

void generate_marble(std::vector<std::tuple<float, float, float>> &image,
                     int width, int height, std::vector<double> &noise) {

    std::tuple<float, float, float> color;

    double periodX = 5.0;
    double periodY = 10.0;

    double turbulencePower = 5.0;
    double turbulenceSize = 32.0;

    double xy_value = 0.0;
    double sine_value = 0.0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            xy_value = x * periodX / width + y * periodY / height +
                       turbulencePower *
                           turbulence(double(x), double(y), width, height,
                                      turbulenceSize, noise) /
                           255.0;
            sine_value = 256 * fabs(sin(xy_value * M_PI));
            color = std::make_tuple(float(sine_value / 255.0f),
                                    float(sine_value / 255.0f),
                                    float(sine_value / 255.0f));
            image[get_index(x, y, width)] = color;
        }
    }
}

static void update_x_and_y(int r, std::tuple<int, int> &walk1,
                           std::tuple<int, int> &walk2, int width, int height) {

    int x1, y1, x2, y2;
    std::tie(x1, y1) = walk1;
    std::tie(x2, y2) = walk2;

    switch (r) {
    case 0:
        x1 += 1;
        x2 -= 1;
        break;
    case 1:
        x1 -= 1;
        x2 += 1;
        break;
    case 2:
        y1 += 1;
        y2 -= 1;
        break;
    case 3:
        y1 -= 1;
        y2 += 1;
        break;
    }

    if (x1 < 0)
        x1 = 0;
    else if (x1 > width - 1)
        x1 = width - 1;

    if (x2 < 0)
        x2 = 0;
    else if (x2 > width - 1)
        x2 = width - 1;

    if (y1 < 0)
        y1 = 0;
    else if (y1 > height - 1)
        y1 = height - 1;

    if (y2 < 0)
        y2 = 0;
    else if (y2 > height - 1)
        y2 = height - 1;

    walk1 = std::make_tuple(x1, y1);
    walk2 = std::make_tuple(x2, y2);
};
