#pragma once
#ifndef COLOR_H
#define COLOR_H

#include"Vector3.h"

#include<iostream>

void WriteColor(std::ostream& out, Color pixelColor)
{
    out << static_cast<int>(255.999 * pixelColor.X()) << ' '
        << static_cast<int>(255.999 * pixelColor.Y()) << ' '
        << static_cast<int>(255.999 * pixelColor.Z()) << '\n';
}
#endif // !COLOR_H

