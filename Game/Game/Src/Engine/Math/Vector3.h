// @file: Vector3.h
//
// @brief: Header file for Vector3 class.

#pragma once
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3() = default;
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float Magnitude() const;
	void Normalize();
	
	float Distance(const Vector3&) const;

	Vector3 Dot(const Vector3&) const;
	Vector3 Cross(const Vector3&) const;

	// ---------------------- Operator overloaders ----------------------

	Vector3 operator+(const Vector3& other) const
	{
		Vector3 result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;
		result.z = this->z + other.z;
		return result;
	}

	Vector3 operator-(const Vector3& other) const
	{
		Vector3 result;
		result.x = this->x - other.x;
		result.y = this->y - other.y;
		result.z = this->z - other.z;
		return result;
	}

	// Dot product
	Vector3 operator*(const Vector3& other) const
	{
		Vector3 result;
		result.x = this->x * other.x;
		result.y = this->y * other.y;
		result.z = this->z * other.z;
		return result;
	}

	Vector3 operator*(float other) const
	{
		Vector3 result;
		result.x = this->x * other;
		result.y = this->y * other;
		result.z = this->z * other;
		return result;
	}

	Vector3& operator+=(const Vector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}
	
	// Dot product
	Vector3& operator*=(const Vector3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vector3& operator*=(float other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
		return *this;
	}

};

#endif // !_Vector3_H_
