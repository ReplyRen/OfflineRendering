#include "RTWeekend.h"

#include <iostream>
#include <fstream>


#include"Color.h"
#include "HittableList.h"
#include "Sphere.h"

using namespace std;

Color RayColor(const Ray& r,const Hittable& world)
{
	HitRecord rec;
	if (world.Hit(r, 0, infinity, rec))
		return 0.5f * (rec.normal, Color(1, 1, 1));
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

	//world

	HittableList world;
	world.Add(make_shared<Hittable>(Point3(0, 0, -1), 0.5));
	world.Add(make_shared<Hittable>(Point3(0, -100.5, -1), 100));

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
			Color pixelColor = RayColor(r, world);
			WriteColor(outImage, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";

}