#ifndef CORE_FILE_H
#define CORE_FILE_H

#include "core.h"
#include <string>
#include <tuple>

namespace core_file {

bool start_with_case_insensitive(std::string line, std::string to_match);

std::tuple<int, int> get_width_and_height(const std::string line);

static std::tuple<int, int, int> get_color(const std::string line);

void save_image(Image &image);

void save_image_ppm(Image &image);

void save_image_png(Image &image);

void save_image_jpeg(Image &image);

void read_image(Image &image);

} // namespace core_file

#endif // CORE_FILE_H
