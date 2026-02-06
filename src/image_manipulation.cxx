#include "image_manipulation.h"
#include "logging.h"
#include "utils.h"
#include <format>
#include <tuple>

void negative_image(Image &image) {

    print_message(
        std::format("Applying Negative Effect to Image: {}", image.filename));

    std::tuple<float, float, float> color;
    std::tuple<float, float, float> negative_color;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            color = image.image[get_index(x, y, image.width)];
            negative_color = std::make_tuple((1.0f - std::get<0>(color)),
                                             (1.0f - std::get<1>(color)),
                                             (1.0f - std::get<2>(color)));
            image.image[get_index(x, y, image.width)] = negative_color;
        }
    }

    print_message(std::format("Done Manipulating Image: {}", image.filename));
}

void darken_image(Image &image) {

    print_message(std::format("Darkening Image: {}", image.filename));

    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.image[get_index(x, y, image.width)];
            new_color = std::make_tuple((std::get<0>(old_color) / 2),
                                        (std::get<1>(old_color) / 2),
                                        (std::get<2>(old_color) / 2));
            image.image[get_index(x, y, image.width)] = new_color;
        }
    }

    print_message(std::format("Done Manipulating Image: {}", image.filename));
}
