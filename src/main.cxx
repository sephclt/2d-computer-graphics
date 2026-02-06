#include "file_manager.h"
#include "image_manipulation.h"
#include "structs.h"
#include <string>

int main() {

    std::string in_filename = "SampleImage.ppm";
    std::string out_filename = "DarkenedSampleImage.ppm";

    Image image;
    image.width = 500;
    image.height = 500;
    image.filename = in_filename;

    read_image(image);

    darken_image(image);

    save_image(image, out_filename);

    return 0;
}
