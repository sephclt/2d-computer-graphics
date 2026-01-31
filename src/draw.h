#include <tuple>
#include <vector>

void first_draw(std::vector<std::tuple<float, float, float>> &image, int width,
                int height);

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width,
                 int height, std::tuple<float, float, float> &color);
