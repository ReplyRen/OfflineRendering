#pragma once
#ifndef RAY_H
#define RAY_H

#include"Vector3.h"

class Ray
{
public:
	Point3 orig;
	Vector3 dir;
public:
	Ray(){}
	Ray(const Point3& origin,const Vector3& direction):orig(origin),dir(direction){}
	Point3 Origin()const
	{
		return orig;
	}
	Vector3 Direction()const
	{
		return dir;
	}
	Point3 At(float t)const
	{
		return orig + t * dir;
	}
};

#endif // !RAY_H
