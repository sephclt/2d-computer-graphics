#ifndef CORE_H
#define CORE_H

#include <string>
#include <tuple>
#include <vector>

enum SampleImageType : int;

struct ImageFile {
    std::string filename;
    std::string filetype;
    std::string dimensions;
};

struct ImageTexture {
    std::vector<std::tuple<float, float, float>> texture;
    float noise_value;
    std::tuple<float, float, float> color;

    int width;
    int height;
};

struct Image : ImageFile, ImageTexture {};

namespace core {

bool is_images_equal(Image left, Image right);

SampleImageType parseSampleImageTypeString(std::string type);

SampleImageType parseSampleImageTypeString(char *type);

}; // namespace core

// sample image type for generating sample images
enum SampleImageType : int { GRADIENT, CLOUD, MARBLE, WOOD };

#endif // !CORE_H
