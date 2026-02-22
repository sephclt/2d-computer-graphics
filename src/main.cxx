#include "draw.h"
#include "file_manager.h"
#include "stream.h"
#include <cxxopts.hpp>
#include <string>
#include <tuple>

int main(int argc, char *argv[]) {

    // ARGUMENT PARSING
    cxxopts::Options options("2D Graphics Engine", "Simple 2D Graphics Engine");
    options.add_options()("g, generate", "Generate a PPM image");
    options.add_options()("o, output", "Output file",
                          cxxopts::value<std::string>());
    options.add_options()(
        "t, type", "Sample image to be generated",
        cxxopts::value<SampleImageType>(SampleImageType::GRADIENT)
            ->default_value("gradient"));
    options.add_options()("d, dimension",
                          "Dimension of the image to be generated",
                          cxxopts::value<std::string>());

    // options.add_options()("f,file", "Open homebase with this file",
    //                       cxxopts::value<std::string>()->default_value(""));
    // options.add_options()(
    //     "v,value", "Value to write",
    //     cxxopts::value<std::string>()->default_value("Something"));

    auto result = options.parse(argc, argv);

    if (result["generate"].as<bool>()) {
        const std::string dimension = result["dimension"].as<std::string>();

        std::tuple<int, int> width_and_height = get_width_and_height(dimension);

        auto output = result["output"].as<std::string>();

        auto type = result["type"].as<SampleImageType>();

        generate_image(std::get<0>(width_and_height),
                       std::get<1>(width_and_height), output, type);
    }

    return 0;
}
