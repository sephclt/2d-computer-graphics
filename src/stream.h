#pragma once

#include "draw.h"
#include <istream>
#include <ostream>

std::istream &operator>>(std::istream &is, SampleImageType &type);

std::ostream &operator<<(std::ostream &os, SampleImageType &type);
