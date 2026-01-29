#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::tuple<int, int, int> get_rgb_values(int r, int g, int b) {
  return std::make_tuple(r, g, b);
}

void printRGB(std::tuple<int, int, int> rgb) {
  int r = 0, g = 0, b = 0;

  std::tie(r, g, b) = rgb;
  std::cout << "R: " << r << "\tG: " << g << "\tB: " << b << "\n";
}

void first_draw(std::vector<std::tuple<float, float, float>> &image, int width,
                int height) {
  std::tuple<float, float, float> color;
  int ctr = 0;

  for (int y = height - 1; y >= 0; --y) {
    for (int x = 0; x < width; ++x) {
      float r = float(x) / float(width);
      float g = float(y) / float(height);
      float b = 0.2;
      color = std::make_tuple(r, g, b);
      image[ctr] = color;
      ctr++;
    }
  }
}

void cross_draw(std::vector<std::tuple<float, float, float>> &image, int width,
                int height, int cross_thickness) {
  std::tuple<float, float, float> color;
  int ctr = 0;

  int start_x = width - cross_thickness / 2;
  int end_x = start_x + cross_thickness;

  int start_y = height - cross_thickness / 2;
  int end_y = start_y + cross_thickness;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      bool in_vert_bar = (x >= start_x && x < end_x);
      bool in_horz_bar = (y >= start_y && y < end_y);

      if (in_vert_bar || in_horz_bar) {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        color = std::make_tuple(r, g, b);
        image[ctr] = color;
        ctr++;
      }
    }
  }
}

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

int main() {

  // Tuple
  int r1 = 256, g1 = 256, b1 = 256;
  int r2 = 0, g2 = 0, b2 = 0;
  int r3 = 0, g3 = 0, b3 = 0;

  std::tuple<int, int, int> rgb;

  rgb = get_rgb_values(r1, g1, b1);

  std::cout << "R1: " << r1 << "\tG1: " << g1 << "\tB1: " << b1 << "\n";

  r2 = std::get<0>(rgb);
  g2 = std::get<1>(rgb);
  b2 = std::get<2>(rgb);

  std::cout << "R2: " << r2 << "\tG2: " << g2 << "\tB2: " << b2 << "\n";

  std::tie(r3, g3, b3) = rgb;

  std::cout << "R3: " << r3 << "\tG3: " << g3 << "\tB3: " << b3 << "\n";

  std::tuple<int, int, int> rgb2;

  rgb2 = get_rgb_values(155, 160, 170);

  // Index
  std::vector<std::tuple<int, int, int>> index = {};

  int width = 5, height = 5;

  int x = 2, y = 2;

  int formula = x + (width * y);

  for (int i = 0; i < width * height; i++) {

    if (i == formula) {
      index.push_back(rgb2);
      continue;
    }

    index.push_back(rgb);
  }

  int r = 0, g = 0, b = 0;
  for (int i = 0; i < index.size(); i++) {
    std::tie(r, g, b) = index[i];
    std::cout << "[" << i << "] : " << "R: " << r << "\tG: " << g
              << "\tB: " << b << "\n";
  }

  printRGB(index[formula]);

  // Saving an image
  std::vector<std::tuple<float, float, float>> image;

  width = 500;
  height = 500;

  image.resize(width * height);

  // first_draw(image, width, height);
  cross_draw(image, width, height, 300);

  save_image(image, width, height, "random.ppm");

  return 0;
}
