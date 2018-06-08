#pragma once
class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float, float, float);
	Vec3(const Vec3&);
	~Vec3();

	Vec3& normalize();
	Vec3& operator= (const Vec3&);
	Vec3& operator+(const Vec3&);
	Vec3& operator+=(const Vec3&);
	Vec3& operator-(const Vec3&);
	Vec3& operator*(const float&);
	Vec3& operator*=(const float&);
	Vec3& operator/(const float&);
	Vec3& operator/=(const float&);
	Vec3& operator-=(const Vec3&);
};

