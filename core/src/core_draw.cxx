#include "core_draw.h"
#include "SDL3/SDL_surface.h"
#include "core.h"
#include "core_file.h"
#include "core_log.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

int get_index(int x, int y, int width);
double smooth_noise(double x, double y, int width, int height,
                    std::vector<double> &noise);
double turbulence(double x, double y, int width, int height, double size,
                  std::vector<double> &noise);

void core_draw::generate_image(Image &image, SampleImageType imageType) {
    // Resize Image
    core_log::print_message("Resizing Image!\n");
    image.texture.resize(image.width * image.height);

    core_log::print_message("Clearing Image!\n");
    clear_image(image);

    core_log::print_message("Generating Color!\n");
    image.color = std::make_tuple(0.0f, 0.0f, 0.066667f);

    core_log::print_message("Generating Noise!\n");
    std::vector<double> noise;
    noise.resize(image.width * image.height);
    generate_noise(noise, image);

    switch (imageType) {
    case SampleImageType::GRADIENT:
        generate_gradient(image);
        break;
    case SampleImageType::CLOUD:
        generate_cloud(image, noise);
        break;
    case SampleImageType::MARBLE:
        generate_marble(image, noise);
        break;
    case SampleImageType::WOOD:
        generate_wood(image, noise);
        break;
    default:
        break;
    }

    core_file::save_image(image);
}

void core_draw::clear_image(ImageTexture &image_texture) {
    for (int y = image_texture.height; y > image_texture.height; --y) {
        for (int x = 0; x <= image_texture.width; ++x) {
            image_texture
                .texture[x + image_texture.width * image_texture.height] =
                image_texture.color;
        }
    }
}

void core_draw::generate_gradient(ImageTexture &image_texture) {
    std::cout << "Generating Gradient Image\n";
    std::tuple<float, float, float> color;
    int ctr = 0;

    for (int y = image_texture.height - 1; y >= 0; --y) {
        for (int x = 0; x < image_texture.width; ++x) {
            float r = float(x) / float(image_texture.width);
            float g = float(y) / float(image_texture.height);
            float b = 0.2;
            color = std::make_tuple(r, g, b);
            image_texture.texture[ctr] = color;
            ctr++;
        }
    }
}

void core_draw::generate_noise(std::vector<double> &noise,
                               ImageTexture &image_texture) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    for (int y = 0; y < image_texture.height; ++y) {
        for (int x = 0; x < image_texture.width; ++x) {
            noise[get_index(x, y, image_texture.width)] =
                (image_texture.noise_value + dist(mt));
        }
    }
}

void core_draw::generate_cloud(ImageTexture &image_texture,
                               std::vector<double> &noise) {

    std::tuple<float, float, float> color;
    int c = 0;

    for (int y = 0; y < image_texture.height; ++y) {
        for (int x = 0; x < image_texture.width; ++x) {
            c = int(turbulence(double(x), double(y), image_texture.width,
                               image_texture.height, 64, noise));
            color = std::make_tuple(float(c / 255.0f), float(c / 255.0f),
                                    float(c / 255.0f));
            image_texture.texture[get_index(x, y, image_texture.width)] = color;
        }
    }
}

void core_draw::generate_marble(ImageTexture &image_texture,
                                std::vector<double> &noise) {
    std::tuple<float, float, float> color;

    double periodX = 5.0;
    double periodY = 10.0;

    double turbulencePower = 5.0;
    double turbulenceSize = 32.0;

    double xy_value = 0.0;
    double sine_value = 0.0;

    for (int y = 0; y < image_texture.height; ++y) {
        for (int x = 0; x < image_texture.width; ++x) {
            xy_value =
                x * periodX / image_texture.width +
                y * periodY / image_texture.height +
                turbulencePower *
                    turbulence(double(x), double(y), image_texture.width,
                               image_texture.height, turbulenceSize, noise) /
                    255.0;
            sine_value = 256 * fabs(sin(xy_value * M_PI));
            color = std::make_tuple(float(sine_value / 255.0f),
                                    float(sine_value / 255.0f),
                                    float(sine_value / 255.0f));
            image_texture.texture[get_index(x, y, image_texture.width)] = color;
        }
    }
}

void core_draw::generate_wood(ImageTexture &image_texture,
                              std::vector<double> &noise) {
    std::tuple<float, float, float> color;

    double xy_period = 25.0;
    double turbulence_power = 0.1;
    double turbulence_size = 32.0;

    double sine_value = 0.0;
    double dist_value = 0.0;
    double x_value = 0.0;
    double y_value = 0.0;

    for (int y = 0; y < image_texture.height; ++y) {
        for (int x = 0; x < image_texture.width; ++x) {
            x_value =
                (x - image_texture.width / 2) / double(image_texture.width);
            y_value =
                (y - image_texture.height / 2) / double(image_texture.height);
            dist_value =
                sqrt(x_value * x_value + y_value * y_value) +
                turbulence_power *
                    turbulence(double(x), double(y), image_texture.width,
                               image_texture.height, turbulence_size, noise) /
                    255.0f;
            sine_value = 128.0 * fabs(sin(2 * xy_period * dist_value * M_PI));
            color = std::make_tuple(float((80 + sine_value) / 255.0f),
                                    float((30 + sine_value) / 255.0f),
                                    float(30.0f / 255.0f));
            image_texture.texture[get_index(x, y, image_texture.width)] = color;
        }
    }
}

SDL_Texture *core_draw::create_texture(SDL_Renderer *renderer,
                                       Image &image_texture) {
    // Create a surface with 24-bit RGB format
    SDL_Surface *surface = SDL_CreateSurface(
        image_texture.width, image_texture.height, SDL_PIXELFORMAT_RGB24);

    if (!surface)
        return nullptr;

    Uint8 *pixels = static_cast<Uint8 *>(surface->pixels);

    for (int i = 0; i < image_texture.width * image_texture.height; ++i) {
        auto [r, g, b] = image_texture.texture[i];

        // Convert float [0.0, 1.0] → Uint8 [0, 255]
        pixels[i * 3 + 0] =
            static_cast<Uint8>(std::clamp(r, 0.0f, 1.0f) * 255.0f);
        pixels[i * 3 + 1] =
            static_cast<Uint8>(std::clamp(g, 0.0f, 1.0f) * 255.0f);
        pixels[i * 3 + 2] =
            static_cast<Uint8>(std::clamp(b, 0.0f, 1.0f) * 255.0f);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    return texture;
}

SDL_Surface *core_draw::create_surface(ImageTexture &image_texture) {
    // Create a surface with 24-bit RGB format
    SDL_Surface *surface = SDL_CreateSurface(
        image_texture.width, image_texture.height, SDL_PIXELFORMAT_RGB24);

    if (!surface)
        return nullptr;

    Uint8 *pixels = static_cast<Uint8 *>(surface->pixels);

    for (int i = 0; i < image_texture.width * image_texture.height; ++i) {
        auto [r, g, b] = image_texture.texture[i];

        // Convert float [0.0, 1.0] → Uint8 [0, 255]
        pixels[i * 3 + 0] =
            static_cast<Uint8>(std::clamp(r, 0.0f, 1.0f) * 255.0f);
        pixels[i * 3 + 1] =
            static_cast<Uint8>(std::clamp(g, 0.0f, 1.0f) * 255.0f);
        pixels[i * 3 + 2] =
            static_cast<Uint8>(std::clamp(b, 0.0f, 1.0f) * 255.0f);
    }

    return surface;
}

int get_index(int x, int y, int width) { return x + width * y; }

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
