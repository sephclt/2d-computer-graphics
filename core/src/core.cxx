#include "core.h"

#include <SDL3/SDL.h>
#include <algorithm>
#include <imgui.h>
#include <string>
#include <unordered_map>

// Used for checking if Image objects are the same
// mostly used for cache right now
bool core::is_images_equal(Image left, Image right) {
    if (left.noise_value != right.noise_value)
        return false;

    return true;
}

// getting the sample image type via string
SampleImageType core::parseSampleImageTypeString(std::string type) {

    // Convert to lower case
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    static const std::unordered_map<std::string, SampleImageType> typeMap = {
        {"gradient", SampleImageType::GRADIENT},
        {"cloud", SampleImageType::CLOUD},
        {"marble", SampleImageType::MARBLE},
        {"wood", SampleImageType::WOOD},
    };

    auto it = typeMap.find(type);

    if (it != typeMap.end()) {
        return it->second;
    }

    return SampleImageType::GRADIENT;
}

SampleImageType core::parseSampleImageTypeString(char *type) {

    std::string type_str(type);

    // Convert to lower case
    std::transform(type_str.begin(), type_str.end(), type_str.begin(),
                   ::tolower);

    static const std::unordered_map<std::string, SampleImageType> typeMap = {
        {"gradient", SampleImageType::GRADIENT},
        {"cloud", SampleImageType::CLOUD},
        {"marble", SampleImageType::MARBLE},
        {"wood", SampleImageType::WOOD},
    };

    auto it = typeMap.find(type_str);

    if (it != typeMap.end()) {
        return it->second;
    }

    return SampleImageType::GRADIENT;
}
