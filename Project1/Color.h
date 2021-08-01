#pragma once
#ifndef COLOR_H
#define COLOR_H

#include"Vector3.h"

#include<iostream>

void WriteColor(std::ostream& out, Color pixelColor, int samplePerPixel)
{
	auto r = pixelColor.X();
	auto g = pixelColor.Y();
	auto b = pixelColor.Z();

	auto scale = 1.0f / samplePerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	out << static_cast<int>(255.999 * Clamp(r, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(255.999 * Clamp(g, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(255.999 * Clamp(b, 0.0f, 0.999f)) << '\n';
}
#endif // !COLOR_H

