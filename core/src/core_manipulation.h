#ifndef CORE_MANIPULATION_H

#include "core.h"

#define IMH_BRIGHTEN_ADD 0b01
#define IMH_BRIGHTEN_MUL 0b10
#define IMH_DARKEN_DOUBLE 0b100
#define IMH_DARKEN_HALF 0b1000

namespace core_manipulation {
void darken_image(Image &image, int value);

void brighten_image(Image &image, int type, float value);
} // namespace core_manipulation

#endif // !CORE_MANIPULATION_H
