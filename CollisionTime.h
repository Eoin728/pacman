#pragma once
#include "Math.h"
struct AABB
{
	Vector3 mmax;
	Vector3 mmin;

	void SetMinMax(const Vector3& nw);

	void Rotate(const Quaternion& q);

	float Mindissq(const Vector3& v) const;

	AABB();

	bool IsLeftOrDown(const Vector3& a) const;

	Vector3 MinVec(const Vector3& a) const;
};

struct Sphere
{
	Vector3 mCentre;
	float mRadius;
	
};

struct LineSegment
{
	Vector3 mstart;
	Vector3 mend;

	float MinDisFromLineSq(const Vector3& point) const;
};


struct Capsule
{
	LineSegment mline;
	float mradius;

	
};

//wall and pacman with projectile
bool Intersect(const AABB& a, const Sphere& s);

//pacman with collectible
bool Intersect(const Sphere& a, const Sphere& b);


bool Intersect(const Sphere& s, const Capsule& c);