#include "CollisionTime.h"
#include <array>

void AABB::SetMinMax(const Vector3& nw)
{
	mmin.x = Math::Min(nw.x, mmin.x);
	mmin.y = Math::Min(nw.y, mmin.y);
	mmin.z = Math::Min(nw.z, mmin.z);

	mmax.x = Math::Max(nw.x, mmax.x);
	mmax.y = Math::Max(nw.y, mmax.y);
	mmax.z = Math::Max(nw.z, mmax.z);
}

void AABB::Rotate(const Quaternion& q)
{
	std::array<Vector3, 8> ar;
	ar[0] = mmax;
	ar[1] = mmin;
	ar[2] = Vector3(mmin.x, mmin.y, mmax.z);
	ar[3] = Vector3(mmin.x, mmax.y, mmin.z);
	ar[4] = Vector3(mmax.x, mmin.y, mmin.z);
	ar[5] = Vector3(mmax.x, mmax.y, mmin.z);
	ar[6] = Vector3(mmin.x, mmax.y, mmax.z);
	ar[7] = Vector3(mmax.x, mmin.y, mmax.z);

	mmax = Vector3::Transform(mmax, q);
	mmin = Vector3::Transform(mmin, q);

	for (auto& vec : ar)
	{
		SetMinMax(Vector3::Transform(vec, q));
	}


}


bool Intersect(const AABB& a, const AABB& b)
{
	return (a.mmax.x < b.mmin.x || a.mmin.x > b.mmax.x
		|| a.mmax.y < b.mmin.y || a.mmin.y > b.mmax.y
		|| a.mmax.z < b.mmin.z || a.mmin.z > b.mmax.z
		);
}

AABB::AABB()
{
	mmin.x = Math::Infinity;
	mmin.y = Math::Infinity;
	mmin.z = Math::Infinity;

	mmax.x = Math::NegInfinity;
	mmax.y = Math::NegInfinity;
	mmax.z = Math::NegInfinity;
}
bool Intersect(const AABB& a, const Sphere& s)
{
	
	return (s.mRadius * s.mRadius) > a.Mindissq(s.mCentre);
}

float AABB::Mindissq(const Vector3& v) const
{
	float dx = Math::Max(mmin.x - v.x, 0.0f);
	dx = Math::Max(dx, v.x - mmax.x);

	float dy = Math::Max(mmin.y - v.y, 0.0f);
	dy = Math::Max(dy, v.y - mmax.y);

	float dz = Math::Max(mmin.z - v.z, 0.0f);
	dz = Math::Max(dz, v.z - mmax.z);

	return (dx * dx + dy * dy + dz * dz);
}

Vector3 AABB::MinVec(const Vector3& v) const
{
	float dx = Math::Max(mmin.x - v.x, 0.0f);
	dx = Math::Max(dx, v.x - mmax.x);

	float dy = Math::Max(mmin.y - v.y, 0.0f);
	dy = Math::Max(dy, v.y - mmax.y);

	float dz = Math::Max(mmin.z - v.z, 0.0f);
	dz = Math::Max(dz, v.z - mmax.z);

	return Vector3(dx, dy, dz);


}

//assumes its not in it
bool AABB::IsLeftOrDown(const Vector3& a) const
{
	return mmin.x > a.x || mmin.y > a.y;
}


bool Intersect(const Sphere& s, const Capsule& c)
{
	float radii = (s.mRadius + c.mradius) * (s.mRadius + c.mradius);

	return (radii >= c.mline.MinDisFromLineSq(s.mCentre));
}


float LineSegment::MinDisFromLineSq(const Vector3& p) const
{

	Vector3 x = mstart - mend;
	Vector3 bx = mend - mstart;

	Vector3 ps = p - mstart;
	Vector3 pe = p - mend;

	if (Vector3::Dot(x, ps) <= 0)
	{
		return (ps.LengthSq());
	}
	if (Vector3::Dot(bx, pe) <= 0)
	{
		return (pe.LengthSq());
	}
	
	Vector3 un = Vector3::Normalize(x);

	float adj = Vector3::Dot(un, ps);

	Vector3 m = mstart + adj * un;

	ps = p - m;
	return ps.LengthSq();

}

bool Intersect(const Sphere& a, const Sphere& b)
{
	float d1 = (a.mCentre - b.mCentre).LengthSq();
	float d2 = (a.mRadius + b.mRadius) * (a.mRadius + b.mRadius);

	return d1 < d2;


}