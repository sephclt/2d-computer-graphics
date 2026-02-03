#include "draw.h"
#include "file_manager.h"
#include "logging.h"
#include "utils.h"
#include <format>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

int main() {

    // // Create a Sample Image
    // std::vector<std::tuple<float, float, float>> image;
    // std::vector<std::tuple<float, float, float>> image2;
    // std::tuple<float, float, float> color = std::make_tuple(0, 0, 0);
    // int width = 500, height = 500;
    // std::string filename = "SampleImage.ppm";
    // std::string filename2 = "WalkerImage.ppm";
    //
    // image.resize(width * height);
    // print_message(std::format("Image resized to {}", width * height));
    //
    // first_draw(image, width, height);
    // print_message("Drawn sample draw to image");
    //
    // save_image(image, width, height, filename);
    // print_message(std::format("Successfully saved image {}", filename));
    //
    // // read_image(image2, width, height, filename);
    //
    // image2.resize(width * height);
    // print_message(std::format("Image 2 resized to {}", width * height));
    //
    // clear_image(image2, width, height, color);
    // print_message("Cleared Image 2");
    //
    // walker_draw(image, image2, width, height);
    // print_message("Drawn walker draw to image2");
    //
    // save_image(image2, width, height, filename2);
    // print_message(std::format("Successfully saved image {}", filename2));
    //
    // // XOR, AND, OR draw
    // std::vector<std::tuple<float, float, float>> texture_image;
    //
    // texture_image.resize(width * height);
    // print_message(std::format("TextureImage resized to {}", width * height));
    //
    // clear_image(texture_image, width, height, color);
    //
    // draw_xor(texture_image, width, height);
    // print_message("Drawn xor draw to image2");
    //
    // save_image(texture_image, width, height, "TextureImage.ppm");
    // print_message(
    //     std::format("Successfully saved image {}", "TextureImage.ppm"));

    // GENERATE CLOUD
    std::vector<double> noise;
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float, float, float> color =
        std::make_tuple(0.0f, 0.0f, 0.06666667f);
    int width = 256;
    int height = 256;

    image.resize(width * height);
    print_message("Resized Image");

    clear_image(image, width, height, color);
    print_message("Cleared Image");

    // Generate Noise
    noise.resize(width * height);
    generate_noise(noise, width, height);
    print_message("Generated Noise");

    // Generate Cloud Texture
    generate_cloud(image, width, height, noise);
    print_message("Generated Cloud Texture");
    save_image(image, width, height, "CloudTexture.ppm");
    print_message("Saved Image CloudTexture.ppm");

    // Generate Marble Texture
    generate_marble(image, width, height, noise);
    print_message("Generated Marble Texture");
    save_image(image, width, height, "MarbleTexture.ppm");
    print_message("Saved Image MarbleTexture.ppm");

    // Generate Wood Texture
    generate_wood(image, width, height, noise);
    print_message("Generated Wood Texture");
    save_image(image, width, height, "WoodTexture.ppm");
    print_message("Saved Image WoodTexture.ppm");

    return 0;
}
