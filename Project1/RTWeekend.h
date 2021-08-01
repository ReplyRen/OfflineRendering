#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

inline float DegreeToRadians(float degree)
{
	return degree * pi / 180.0f;
}

inline float Random()
{
	return rand() / (RAND_MAX + 1.0f);
}

inline float Random(float min, float Max)
{
	return min + (Max - min) * Random();
}

inline float Clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#include "Ray.h"
#include "Vector3.h"

#endif
#pragma once
