#include "RTWeekend.h"

#include <iostream>
#include <fstream>


#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

using namespace std;

Color RayColor(const Ray& r, const Hittable& world)
{
	HitRecord rec;
	if (world.Hit(r, 0, infinity, rec)) {
		return 0.5f * (rec.normal + Color(1, 1, 1));
	}
	Vector3 unitDirection = Unit(r.Direction());
	auto t = 0.5f * (unitDirection.Y() + 1.0f);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
	fstream outImage;
	outImage.open("Image.ppm");

	// Image

	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplePrePiexl = 100;

	//world

	HittableList world;
	world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5f));
	world.Add(make_shared<Sphere>(Point3(0, -100.5f, -1), 100));

	// Camera

	Camera cam;

	// Render

	outImage << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			Color pixelColor(0, 0, 0);
			for (int s = 0; s < samplePrePiexl; ++s) {
				auto u = (i + Random()) / (imageWidth - 1);
				auto v = (j + Random()) / (imageHeight - 1);
				Ray r = cam.GetRay(u, v);
				pixelColor += RayColor(r, world);
			}
			WriteColor(outImage, pixelColor, samplePrePiexl);
		}
	}
	std::cerr << "\nDone.\n";

}