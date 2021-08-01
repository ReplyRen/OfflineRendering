#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vector3.h"

class Sphere :public Hittable
{
public:
	Sphere() {}
	Sphere(Point3 cen, float r, shared_ptr<Material>m) :center(cen), radius(r), matPtr(m) {};

	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

public:
	Point3 center;
	float radius;
	shared_ptr<Material>matPtr;
};

bool Sphere::Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
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
	Vector3 outwardNormal = (rec.p - center) / radius;
	rec.SetFaceNormal(r, outwardNormal);
	rec.matPtr = matPtr;

	return true;
}
#endif
