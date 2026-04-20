#ifndef CORE_DRAW_H
#define CORE_DRAW_H

#include "SDL3/SDL_render.h"
#include "core.h"
#include <vector>

namespace core_draw {

void generate_image(Image &image, SampleImageType imageType);

void clear_image(ImageTexture &image_texture);

void generate_gradient(Image &image);

void generate_cloud(Image &image);

void generate_marble(Image &image);

void generate_wood(Image &image);

void generate_noise(std::vector<double> &noise, ImageTexture &image_texture);

SDL_Texture *create_texture(SDL_Renderer *renderer,
                            ImageTexture &image_texture);

} // namespace core_draw

#endif // !CORE_DRAW_H
