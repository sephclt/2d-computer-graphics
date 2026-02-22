#include "file_manager.h"
#include "logging.h"
#include <format>
#include <fstream>

void save_image(std::vector<std::tuple<float, float, float>> &image, int width,
                int height, std::string filename) {

    std::tuple<float, float, float> color;
    std::ofstream out(filename, std::ofstream::out);

    // Write P3
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < (width * height); ++i) {
        color = image[i];
        out << int(std::get<0>(color) * 255.0f) << " "
            << int(std::get<1>(color) * 255.0f) << " "
            << int(std::get<2>(color) * 255.0f) << "\n";
    }
    out.close();
}

void save_image(Image &image) {

    std::tuple<float, float, float> color;
    std::ofstream out(image.filename, std::ofstream::out);

    print_message(std::format("Saving Image: {}", image.filename));

    // Write P3
    out << "P3\n" << image.width << " " << image.height << "\n255\n";

    for (int i = 0; i < (image.width * image.height); ++i) {
        color = image.image[i];
        out << int(std::get<0>(color) * 255.0f) << " "
            << int(std::get<1>(color) * 255.0f) << " "
            << int(std::get<2>(color) * 255.0f) << "\n";
    }

    print_message(std::format("Done Saving Image: {}", image.filename));

    out.close();
}

void read_image(std::vector<std::tuple<float, float, float>> &image, int &width,
                int &height, std::string filename) {
    std::ifstream infile(filename);
    std::tuple<int, int, int> r_color;
    std::tuple<float, float, float> w_color;
    std::tuple<int, int> width_and_height;

    int state = 0;
    bool done = false;
    std::string line;

    while (std::getline(infile, line)) {
        if (start_with_case_insensitive(line, "P3") && state == 0) {
            state = 1;
        }

        if (!start_with_case_insensitive(line, "#") &&
            !start_with_case_insensitive(line, "P3") && state == 1) {
            width_and_height = get_width_and_height(line);
            width = std::get<0>(width_and_height);
            height = std::get<1>(width_and_height);
            state = 2;
        }

        if (start_with_case_insensitive(line, "255") && state == 2) {
            state = 3;
        }

        if (!(line.compare("255") == 0) && state == 3) {
            r_color = get_color(line);
            w_color = std::make_tuple(float(std::get<0>(r_color) / 255.0f),
                                      float(std::get<1>(r_color) / 255.0f),
                                      float(std::get<2>(r_color) / 255.0f));
            image.push_back(w_color);
            done = true;
        }
    }

    infile.close();
}

void read_image(Image &image) {

    std::ifstream infile(image.filename);
    std::tuple<int, int, int> r_color;
    std::tuple<float, float, float> w_color;
    std::tuple<int, int> width_and_height;

    int state = 0;
    bool done = false;
    std::string line;

    print_message(std::format("Reading Image: {}", image.filename));

    while (std::getline(infile, line)) {
        if (start_with_case_insensitive(line, "P3") && state == 0) {
            state = 1;
        }

        if (!start_with_case_insensitive(line, "#") &&
            !start_with_case_insensitive(line, "P3") && state == 1) {
            width_and_height = get_width_and_height(line);
            image.width = std::get<0>(width_and_height);
            image.height = std::get<1>(width_and_height);
            state = 2;
        }

        if (start_with_case_insensitive(line, "255") && state == 2) {
            state = 3;
        }

        if (!(line.compare("255") == 0) && state == 3) {
            r_color = get_color(line);
            w_color = std::make_tuple(float(std::get<0>(r_color) / 255.0f),
                                      float(std::get<1>(r_color) / 255.0f),
                                      float(std::get<2>(r_color) / 255.0f));
            image.image.push_back(w_color);
            done = true;
        }
    }

    print_message(std::format("Done Reading Image: {}", image.filename));

    infile.close();
}

inline bool start_with_case_insensitive(std::string line,
                                        std::string to_match) {
    // Convert to lower case
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    std::transform(to_match.begin(), to_match.end(), to_match.begin(),
                   ::tolower);

    if (line.find(to_match) == 0) {
        return true;
    } else {
        return false;
    }
}

std::tuple<int, int> get_width_and_height(const std::string line) {
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = line.find_first_not_of(" ", end)) != std::string::npos) {
        end = line.find(" ", start);
        out.push_back(line.substr(start, end - start));
    }

    int w = std::stoi(out[0]);
    int h = std::stoi(out[1]);

    return std::make_tuple(w, h);
}

std::tuple<int, int, int> get_color(const std::string line) {
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = line.find_first_not_of(" ", end)) != std::string::npos) {
        end = line.find(" ", start);
        out.push_back(line.substr(start, end - start));
    }

    int r = std::stoi(out[0]);
    int g = std::stoi(out[1]);
    int b = std::stoi(out[2]);

    return std::make_tuple(r, g, b);
}
