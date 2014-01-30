#pragma once
#include <iostream>
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
using namespace std;

struct Vector3{
public:
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float vx,float vy,float vz);
	Vector3(glm::vec3);
	Vector3 operator+(const Vector3& other);

	friend ostream &operator<<(ostream& steam, const Vector3& item);
	glm::vec3 ToGLMVector3f();
	glm::vec4 ToGLMVector4f();

};