#pragma once
#include <cmath>
#include <memory>
#include <limits>
namespace Math
{
	const float Pi = 3.14159265358979323846f;
	const float HalfPi = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float Cos(float a)
	{
		return cosf(a);
	}
	inline float Sin(float a)
	{
		return sinf(a);
	}

	
	inline float ACos(float a)
	{
		return acosf(a);
	}


	inline float Sqrt(float x)
	{
		return sqrtf(x);
	}

	inline float Max(float a, float b)
	{
		if (a > b)
			return a;
		return b;
	}

	inline float Min(float a, float b)
	{
		if (a < b)
			return a;
		return b;
	}
	inline float ToRadians(float a)
	{
		return a * Pi / 180.0f;
	}

	inline float ToDegrees(float a)
	{
		return a * 180.0f / Pi;
	}

	inline bool NearZero(float a)
	{
		return (a <= 0.001f && a >= -0.001f);
	}

	inline float Abs(float a)
	{
		if (a < 0)
			a *= -1.0f;
		return a;
	}
	
}

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
		*this = Vector3::Zero;
	}

	Vector3(float a,float b,float c):x{a},y{b},z{c}{}

	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp;
		tmp.x = a.x - b.x;
		tmp.y = a.y - b.y;
		tmp.z = a.z - b.z;
		return tmp;
	}

	friend Vector3 operator*(float a, const Vector3& b)
	{
		Vector3 tmp;
		tmp.x = a * b.x;
		tmp.y = a * b.y;
		tmp.z = a * b.z;
		return tmp;
	}

	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp;
		tmp.x = a.x + b.x;
		tmp.y = a.y + b.y;
		tmp.z = a.z + b.z;
		return tmp;
	}

	Vector3& operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	Vector3& Normalize()
	{
		float l = Length();
	x /= l;
		y /= l;
		z /= l;
		return *this;
	}
	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}
	 float LengthSq()
	{
		return x *x + y * y + z * z;
	}

	 float Length()
	{
		return Math::Sqrt(LengthSq());
	}

	 static float Dot(const Vector3& a, const Vector3& b)
	 {
		 return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	 static Vector3 Cross(const Vector3& a, const Vector3& b)
	 {
		 Vector3 temp;
		 temp.x = a.y * b.z - a.z * b.y;
		 temp.y = a.z * b.x - a.x * b.z;
		 temp.z = a.x * b.y - a.y * b.x;
		 return temp;
	 }

	static Vector3 Transform(const Vector3& a, const class Quaternion& q);
	
	static Vector3 Transform(const Vector3& a, const class Matrix4& m,float w = 1.0f);




	 static const Vector3 UnitX;
	 static const Vector3 UnitZ;
	 static const Vector3 UnitY;
	static const Vector3 Zero;

};


class Quaternion
{
public:
	float i;
	float j;
	float k;
	float s;

	Quaternion(float a, float b, float c,float d):i{ a }, j{ b }, k{ c }, s{d}{}

	Quaternion() { *this = Quaternion::Identity; }

	//a is normalised axis, s is angle of rotation
	Quaternion(const Vector3& a, float x)
	{
		s = Math::Cos(x / 2);

		float n = Math::Sin(x / 2);

		i = a.x * n;
		j = a.y * n;
		k = a.z * n;
	}

	friend Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		Quaternion c;
		Vector3 va = Vector3(a.i, a.j, a.k);
		Vector3 vb = Vector3(b.i, b.j,b.k);
		
		Vector3 im = b.s * va + a.s * vb + Vector3::Cross(va, vb);
		c.i = im.x;
		c.j = im.y;
		c.k = im.z;
		c.s = a.s * b.s - Vector3::Dot(va, vb);

		return c;
	}


	static const Quaternion Identity;

};

class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	Matrix4(float matrix[4][4])
	{
		memcpy(mat, matrix, 16 * sizeof(float));
	}

	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
			Matrix4 retVal;
			
			retVal.mat[0][0] =
				a.mat[0][0] * b.mat[0][0] +
				a.mat[0][1] * b.mat[1][0] +
				a.mat[0][2] * b.mat[2][0] +
				a.mat[0][3] * b.mat[3][0];

			retVal.mat[0][1] =
				a.mat[0][0] * b.mat[0][1] +
				a.mat[0][1] * b.mat[1][1] +
				a.mat[0][2] * b.mat[2][1] +
				a.mat[0][3] * b.mat[3][1];

			retVal.mat[0][2] =
				a.mat[0][0] * b.mat[0][2] +
				a.mat[0][1] * b.mat[1][2] +
				a.mat[0][2] * b.mat[2][2] +
				a.mat[0][3] * b.mat[3][2];

			retVal.mat[0][3] =
				a.mat[0][0] * b.mat[0][3] +
				a.mat[0][1] * b.mat[1][3] +
				a.mat[0][2] * b.mat[2][3] +
				a.mat[0][3] * b.mat[3][3];

		
			retVal.mat[1][0] =
				a.mat[1][0] * b.mat[0][0] +
				a.mat[1][1] * b.mat[1][0] +
				a.mat[1][2] * b.mat[2][0] +
				a.mat[1][3] * b.mat[3][0];

			retVal.mat[1][1] =
				a.mat[1][0] * b.mat[0][1] +
				a.mat[1][1] * b.mat[1][1] +
				a.mat[1][2] * b.mat[2][1] +
				a.mat[1][3] * b.mat[3][1];

			retVal.mat[1][2] =
				a.mat[1][0] * b.mat[0][2] +
				a.mat[1][1] * b.mat[1][2] +
				a.mat[1][2] * b.mat[2][2] +
				a.mat[1][3] * b.mat[3][2];

			retVal.mat[1][3] =
				a.mat[1][0] * b.mat[0][3] +
				a.mat[1][1] * b.mat[1][3] +
				a.mat[1][2] * b.mat[2][3] +
				a.mat[1][3] * b.mat[3][3];

		
			retVal.mat[2][0] =
				a.mat[2][0] * b.mat[0][0] +
				a.mat[2][1] * b.mat[1][0] +
				a.mat[2][2] * b.mat[2][0] +
				a.mat[2][3] * b.mat[3][0];

			retVal.mat[2][1] =
				a.mat[2][0] * b.mat[0][1] +
				a.mat[2][1] * b.mat[1][1] +
				a.mat[2][2] * b.mat[2][1] +
				a.mat[2][3] * b.mat[3][1];

			retVal.mat[2][2] =
				a.mat[2][0] * b.mat[0][2] +
				a.mat[2][1] * b.mat[1][2] +
				a.mat[2][2] * b.mat[2][2] +
				a.mat[2][3] * b.mat[3][2];

			retVal.mat[2][3] =
				a.mat[2][0] * b.mat[0][3] +
				a.mat[2][1] * b.mat[1][3] +
				a.mat[2][2] * b.mat[2][3] +
				a.mat[2][3] * b.mat[3][3];

			
			retVal.mat[3][0] =
				a.mat[3][0] * b.mat[0][0] +
				a.mat[3][1] * b.mat[1][0] +
				a.mat[3][2] * b.mat[2][0] +
				a.mat[3][3] * b.mat[3][0];

			retVal.mat[3][1] =
				a.mat[3][0] * b.mat[0][1] +
				a.mat[3][1] * b.mat[1][1] +
				a.mat[3][2] * b.mat[2][1] +
				a.mat[3][3] * b.mat[3][1];

			retVal.mat[3][2] =
				a.mat[3][0] * b.mat[0][2] +
				a.mat[3][1] * b.mat[1][2] +
				a.mat[3][2] * b.mat[2][2] +
				a.mat[3][3] * b.mat[3][2];

			retVal.mat[3][3] =
				a.mat[3][0] * b.mat[0][3] +
				a.mat[3][1] * b.mat[1][3] +
				a.mat[3][2] * b.mat[2][3] +
				a.mat[3][3] * b.mat[3][3];

			return retVal;


	}

	Matrix4& operator*=(const Matrix4& a)
	{
		*this = *this * a;
		return *this;
	}

	static Matrix4 CreateScale(float scale)
	{
		float ma[4][4] =
		{
			{scale,0.0f,0.0f,0.0f},
		{0.0f,scale,0.0f,0.0f},
		{0.0f,0.0f,scale,0.0f},
		{0.0f,0.0f,0.0f,1.0f}
		};
		return Matrix4(ma);
	}

	static Matrix4 CreateRotation(const Quaternion& q)
	{
		float mat[4][4];

		mat[0][0] = 1.0f - 2.0f * q.j * q.j - 2.0f * q.k * q.k;
		mat[0][1] = 2.0f * q.i * q.j + 2.0f * q.s * q.k;
		mat[0][2] = 2.0f * q.i * q.k - 2.0f * q.s * q.j;
		mat[0][3] = 0.0f;

		mat[1][0] = 2.0f * q.i * q.j - 2.0f * q.s * q.k;
		mat[1][1] = 1.0f - 2.0f * q.i * q.i - 2.0f * q.k * q.k;
		mat[1][2] = 2.0f * q.j * q.k + 2.0f * q.s * q.i;
		mat[1][3] = 0.0f;

		mat[2][0] = 2.0f * q.i * q.k + 2.0f * q.s * q.j;
		mat[2][1] = 2.0f * q.j * q.k - 2.0f * q.s * q.i;
		mat[2][2] = 1.0f - 2.0f * q.i * q.i - 2.0f * q.j * q.j;
		mat[2][3] = 0.0f;

		mat[3][0] = 0.0f;
		mat[3][1] = 0.0f;
		mat[3][2] = 0.0f;
		mat[3][3] = 1.0f;

		return Matrix4(mat);
	}

	const float * GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}




	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		float ma[4][4] =
		{
			{1.0f,0.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f,0.0f},
		{0.0f,0.0f,1.0f,0.0f},
		{trans.x,trans.y,trans.z,1.0f}
		};
		return Matrix4(ma);
	}


	static Matrix4 CreateView(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::Normalize(( target - eye));
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
		Vector3 t;
		t.x = -Vector3::Dot(xaxis, eye);
		t.y = -Vector3::Dot(yaxis, eye);
		t.z = -Vector3::Dot(zaxis, eye);

		float may[4][4] =
		{
			{xaxis.x,yaxis.x,zaxis.x,0.0f},
			{xaxis.y,yaxis.y,zaxis.y,0.0f},
			{xaxis.z,yaxis.z,zaxis.z,0.0f},
			{t.x,t.y,t.z,1.0f}
			
			
			
		};
		return Matrix4(may);
	}

	static Matrix4 CreateProj(float near, float far,float fov,float height,float width)
	{

		float ma[4][4] =
		{
			{1 / ((width / height) * tanf(fov / 2)),0.0f,0.0f,0.0f},
			{0.0f,1 / (tanf(fov / 2)),0.0f,0.0f},
			{0.0f,0.0f,far / (far - near),1.0f},
			{0.0f,0.0f,-near * far / (far - near),0.0f}
		};
		return Matrix4(ma);


	}

	void Invert();

	
	static const Matrix4 Identity;

};