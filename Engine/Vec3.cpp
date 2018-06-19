#include "stdafx.h"
#include "Vec3.h"


Vec3::Vec3() : x(0), y(0), z(0)
{
}

Vec3::Vec3(const float& x, const float& y, const float& z) 
				: x(x), y(y), z(z)
{
}

Vec3::Vec3(const Vec3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}



Vec3::~Vec3()
{
}

Vec3& Vec3::normalize()
{
	float l = sqrt(pow(x,2) + pow(y,2) + pow(z,2)); 
	x /= l;
	y /= l;
	z /= l;
	return *this;
}

Vec3& Vec3::operator=(const Vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}



Vec3& Vec3::operator+(const Vec3& v)
{
	Vec3 tmp = Vec3(x, y, z);
	x += v.x;
	y += v.y;
	z += v.z;
	return tmp;
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3& Vec3::operator-(const Vec3& v)
{
	Vec3 tmp = Vec3(x,y,z);
	x -= v.x;
	y -= v.y;
	z -= v.z;
	
	return tmp;
}

Vec3& Vec3::operator-=(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3& Vec3::operator*(const float& val)
{
	Vec3 tmp = Vec3(x, y, z);
	x *= val;
	y *= val;
	z *= val;
	return tmp;
}


Vec3& Vec3::operator*=(const float& val)
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}


Vec3& Vec3::operator/(const float& val)
{
	Vec3 tmp = Vec3(x, y, z);
	x /= val;
	y /= val;
	z /= val;
	return tmp;
}



Vec3& Vec3::operator/=(const float& val)
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}

