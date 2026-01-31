#include "draw.h"
#include "file_manager.h"
#include "logging.h"
#include <format>
#include <string>
#include <tuple>
#include <vector>

int main() {

    std::vector<std::tuple<float, float, float>> image;
    std::vector<std::tuple<float, float, float>> image2;
    std::tuple<float, float, float> color = std::make_tuple(0, 0, 0);
    int width = 500, height = 500;
    std::string filename = "SampleImage.ppm";

    image.resize(width * height);
    print_message(std::format("Image resized to {}", width * height));

    first_draw(image, width, height);
    print_message("Drawn sample draw to image");

    save_image(image, width, height, filename);
    print_message(std::format("Successfully saved image {}", filename));

    read_image(image2, width, height, filename);

    image2.resize(width * height);
    print_message(std::format("Image 2 resized to {}", width * height));

    clear_image(image2, width, height, color);
    print_message("Cleared Image 2");

    return 0;
}
