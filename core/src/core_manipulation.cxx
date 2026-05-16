#include "core_manipulation.h"
#include "core_log.h"
#include "core_utils.h"
#include <format>

void core_manipulation::darken_image(Image &image, int value) {
    std::tuple<float, float, float> old_color;
    std::tuple<float, float, float> new_color;

    float darken_value = (value & IMH_DARKEN_DOUBLE) ? 2.0f : 1.5f;

    core_log::print_message(
        std::format("Darkening Image with value: {}", darken_value));

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            old_color = image.texture[core_utils::get_index(x, y, image.width)];
            new_color =
                std::make_tuple((std::get<0>(old_color) / darken_value),
                                (std::get<1>(old_color) / darken_value),
                                (std::get<2>(old_color) / darken_value));
            image.texture[core_utils::get_index(x, y, image.width)] = new_color;
        }
    }

    core_log::print_message(
        std::format("Done Manipulating Image: {}", image.filename));
}
