#include <iostream>
#include <fstream>
#include"Color.h"
#include"Vector3.h"
#include "Ray.h"

using namespace std;

Color RayColor(const Ray& r)
{
	Vector3 unitDirection = Unit(r.Direction());
	auto t = 0.5f * (unitDirection.Y() + 1.0f);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
	ofstream outImage;
	outImage.open("Image.ppm");

	// Image

	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// Camera
	
	auto viewportHeight = 2.0;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	auto origin = Point3(0, 0, 0);
	auto horizontal = Vector3(viewportWidth, 0, 0);
	auto vertical = Vector3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focalLength);



	// Render

	outImage << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			auto u = float(i) / (imageWidth - 1);
			auto v = float(j) / (imageHeight - 1);
			Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			Color pixelColor = RayColor(r);
			WriteColor(outImage, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";

}