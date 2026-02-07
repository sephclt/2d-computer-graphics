#include "image_manipulation.h"
#include "logging.h"
#include "utils.h"
#include <algorithm>
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

void darken_image(Image &image, DarkenValue value) {

    print_message(std::format("Darkening Image: {}", image.filename));

    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    float darken_value = (value = DarkenValue::DOUBLE) ? 2.0f : 1.5f;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.image[get_index(x, y, image.width)];
            new_color =
                std::make_tuple((std::get<0>(old_color) / darken_value),
                                (std::get<1>(old_color) / darken_value),
                                (std::get<2>(old_color) / darken_value));
            image.image[get_index(x, y, image.width)] = new_color;
        }
    }

    print_message(std::format("Done Manipulating Image: {}", image.filename));
}

void brighten_image(Image &image, BrightenType type, float value) {

    print_message(std::format("Brightening Image: {}", image.filename));

    if (type == BrightenType::MULTIPLY)
        brighten_image_multiply(image, value);
    else
        brighten_image_add(image, value);

    print_message(std::format("Done Manipulating Image: {}", image.filename));
}

void brighten_image_multiply(Image &image, float value) {

    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.image[get_index(x, y, image.width)];
            new_color = std::make_tuple(
                std::clamp(std::get<0>(old_color) * value, 0.0f, 1.0f),
                std::clamp(std::get<1>(old_color) * value, 0.0f, 1.0f),
                std::clamp(std::get<2>(old_color) * value, 0.0f, 1.0f));
            image.image[get_index(x, y, image.width)] = new_color;
        }
    }
}

void brighten_image_add(Image &image, float value) {

    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.image[get_index(x, y, image.width)];
            new_color = std::make_tuple(
                std::clamp(std::get<0>(old_color) + value, 0.0f, 1.0f),
                std::clamp(std::get<1>(old_color) + value, 0.0f, 1.0f),
                std::clamp(std::get<2>(old_color) + value, 0.0f, 1.0f));
            image.image[get_index(x, y, image.width)] = new_color;
        }
    }
}

void subtract_image(Image &image, float value) {

    print_message(
        std::format("Subtracting {} to Image {}", value, image.filename));

    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.image[get_index(x, y, image.width)];
            new_color = std::make_tuple(
                std::clamp(std::get<0>(old_color) - value, 0.0f, 1.0f),
                std::clamp(std::get<1>(old_color) - value, 0.0f, 1.0f),
                std::clamp(std::get<2>(old_color) - value, 0.0f, 1.0f));
            image.image[get_index(x, y, image.width)] = new_color;
        }
    }

    print_message(std::format("Done Manipulating Image {}", image.filename));
}

void greyscale_image(Image &image) {

    print_message(std::format("Greyscaling Image {}", image.filename));

    std::tuple<float, float, float> color;
    float c = 0.0f;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            color = image.image[get_index(x, y, image.width)];
            c = (0.2126 * std::get<0>(color)) + (0.7152 * std::get<1>(color)) +
                (0.0722 * std::get<2>(color));
            image.image[get_index(x, y, image.width)] =
                std::make_tuple(c, c, c);
        }
    }

    print_message(std::format("Done Manipulating Image {}", image.filename));
}
