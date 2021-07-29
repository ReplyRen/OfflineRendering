#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vector3.h"

class Sphere :public Hittable
{
public:
	Sphere(){}
	Sphere(Point3 cen, float r) :center(cen), radius(r) {};

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
	
public:
	Point3 center;
	float radius;
};

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec)
{
	Vector3 oc = r.Origin() - center;
	auto a = r.Direction().LengthSquared();
	auto halfB = Dot(oc, r.Direction());
	auto c = oc.LengthSquared() - radius * radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0)return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-halfB - sqrtd) / a;
	if (root < tMin || tMax < root) {
		root = (-halfB + sqrtd) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	rec.t = root;
	rec.p = r.At(rec.t);
	rec.normal = (rec.p - center) / radius;

	return true;
}
#endif
