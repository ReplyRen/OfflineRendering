#include "RTWeekend.h"

#include <iostream>
#include <fstream>


#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

using namespace std;

Color RayColor(const Ray& r, const Hittable& world, int depth)
{
	HitRecord rec;

	if (depth <= 0) {
		return Color(0, 0, 0);
	}

	if (world.Hit(r, 0.001, infinity, rec)) {
		Ray scattered;
		Color attenuation;
		if (rec.matPtr->scatter(r, rec, attenuation, scattered))
			return attenuation * RayColor(scattered, world, depth - 1);
		return Color(0, 0, 0);
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
	const int maxDepth = 50;

	//world

	HittableList world;

	auto materialGround = make_shared<Lambertian>(Color(0.8f, 0.8f, 0));
	auto materialCenter = make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
	auto materialLeft = make_shared<Metal>(Color(0.8f, 0.8f, 0.8f),0);
	auto materialRight = make_shared<Metal>(Color(0.8f, 0.6f, 0.2f),1);

	world.Add(make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
	world.Add(make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
	world.Add(make_shared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
	world.Add(make_shared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));

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
				pixelColor += RayColor(r, world, maxDepth);
			}
			WriteColor(outImage, pixelColor, samplePrePiexl);
		}
	}
	std::cerr << "\nDone.\n";

}