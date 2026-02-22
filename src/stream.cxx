#include "stream.h"
#include "draw.h"
#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

std::istream &operator>>(std::istream &is, SampleImageType &type) {

    std::string token;
    is >> token;

    std::transform(token.begin(), token.end(), token.begin(), ::tolower);

    if (token == "gradient")
        type = SampleImageType::GRADIENT;
    else if (token == "walker")
        type = SampleImageType::WALKER;
    else if (token == "cloud")
        type = SampleImageType::CLOUD;
    else if (token == "marble")
        type = SampleImageType::MARBLE;
    else if (token == "wood")
        type = SampleImageType::WOOD;
    else
        throw std::invalid_argument("Unknown Sample Image Type: " + token);

    return is;
}

std::ostream &operator<<(std::ostream &os, SampleImageType &type) {

    switch (type) {
    case SampleImageType::GRADIENT:
        os << "train";
        break;
    case SampleImageType::WALKER:
        os << "walker";
        break;
    case SampleImageType::CLOUD:
        os << "cloud";
        break;
    case SampleImageType::MARBLE:
        os << "marble";
        break;
    case SampleImageType::WOOD:
        os << "wood";
        break;
    default:
        os << "(unknown)";
        break;
    }

    return os;
}
