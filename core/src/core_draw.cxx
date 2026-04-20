#include "core_draw.h"
#include "core.h"
#include "core_file.h"
#include "core_log.h"
#include <random>
#include <tuple>
#include <vector>

int get_index(int x, int y, int width);

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
        generate_cloud(image);
        break;
    case SampleImageType::MARBLE:
        generate_marble(image);
        break;
    case SampleImageType::WOOD:
        generate_wood(image);
        break;
    default:
        break;
    }

    core_file::save_image(image);
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

int get_index(int x, int y, int width) { return x + width * y; }
