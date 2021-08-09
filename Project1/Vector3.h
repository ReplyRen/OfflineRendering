#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include<iostream>

using std::sqrt;

class Vector3
{
public:
	float e[3];
public:
	Vector3() :e{ 0,0,0 } {}
	Vector3(float e0, float e1, float e2) :e{ e0,e1,e2 } {}

	float X() const
	{
		return e[0];
	}
	float Y()const
	{
		return e[1];
	}
	float Z()const
	{
		return e[2];
	}
	Vector3 operator-() const
	{
		return Vector3(-e[0], -e[1], -e[2]);
	}
	float operator[](int i)const
	{
		return e[i];
	}
	float& operator[](int i)
	{
		return e[i];
	}
	Vector3& operator+=(const Vector3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}
	Vector3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	Vector3& operator/=(const float t)
	{
		return *this *= 1 / t;
	}
	float Length() const
	{
		return sqrt(LengthSquared());
	}
	float LengthSquared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static Vector3 RandomVec3()
	{
		return Vector3(Random(), Random(), Random());
	}

	inline static Vector3 RandomVec3(float min, float max)
	{
		return Vector3(Random(min, max), Random(min, max), Random(min, max));
	}
	bool NearZero() const
	{
		const auto s = 1e-8f;
		return(fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

};

inline std::ostream& operator <<(std::ostream& out, const Vector3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(float t, const Vector3& v)
{
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3& v, float t)
{
	return t * v;
}

inline Vector3 operator/(const Vector3& v, float t)
{
	return (1 / t) * v;
}

inline float Dot(const Vector3& u, const Vector3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline Vector3 Unit(Vector3 v)
{
	return v / v.Length();
}

Vector3 RandomInUnitSphere()
{
	while (true) {
		auto p = Vector3::RandomVec3(-1, 1);
		if (p.LengthSquared() >= 1)
			continue;
		return p;
	}
}

Vector3 RandomUnitVector()
{
	return Unit(RandomInUnitSphere());
}

Vector3 Reflect(const Vector3& v, const Vector3& n)
{
	return v - 2 * Dot(v, n) * n;
}


using Point3 = Vector3;
using Color = Vector3;

#endif

