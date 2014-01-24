#pragma once
#include <iostream>
using namespace std;

struct Vector3{
public:
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float vx,float vy,float vz);

	Vector3 operator+(const Vector3& other);

	friend ostream &operator<<(ostream& steam, const Vector3& item);
};