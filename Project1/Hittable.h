#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord
{
	Point3 p;
	Vector3 normal;
	double t;
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};

#endif