#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

inline float DegreeToRadians(float degree)
{
	return degree * pi / 180.0f;
}

#include "Ray.h"
#include "Vector3.h"

#endif
#pragma once
