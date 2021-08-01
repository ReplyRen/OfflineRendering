#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord
{
	Point3 p;
	Vector3 normal;
	float t;
	bool frontFace;

	inline void SetFaceNormal(const Ray& r, const Vector3& outwardNormal)
	{
		frontFace = Dot(r.Direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};

#endif