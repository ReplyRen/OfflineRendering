#ifndef MATERIAL_H
#define MATERIAL_H

#include "RTWeekend.h"

struct HitRecord;

class Material
{
public:
	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered)const = 0;
};

class Lambertian :public Material
{
public:
	Lambertian(const Color& a) :albedo(a) {}
	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override
	{
		auto scatterDirection = rec.normal + RandomUnitVector();

		if (scatterDirection.NearZero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

public:
	Color albedo;
};

class Metal :public Material
{
public:
	Metal(const Color& a,float f) :albedo(a),fuzz(f<1?f:1) {}

	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered)const override
	{
		Vector3 reflected = Reflect(rIn.Direction(), rec.normal);
		scattered = Ray(rec.p, reflected+fuzz*RandomInUnitSphere());
		attenuation = albedo;
		return (Dot(scattered.Direction(), rec.normal) > 0);
	}
public:
	Color albedo;
	float fuzz;
};

#endif
#pragma once
