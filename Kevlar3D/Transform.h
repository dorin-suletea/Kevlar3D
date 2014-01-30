#pragma once
#include "Vector.h"
#include "GLIncludes.h"
#include "Material.h"
#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"
using namespace glm;

class Transform
{
private:
	Vector3 scale;
	Vector3 position;
	Vector3 rotationEulerAngles;
	vec4 forward;


	GLuint positionUniformPtr;
	GLuint scaleUniformPtr;
	GLuint rotationUniformPtr;

	mat4 rotationMatrix;
	Material* phisicsMaterial;


	bool isDirty;
	void updateScale();
	void updatePosition();
	void updateRotation();



public:
	Transform(Material* vPhisicsMaterial);
	~Transform(void);

	void SetPosition(Vector3 vPosition);
	Vector3 GetPosition();

	void SetScale(Vector3 scale);
	void SetScale(float scale);


	void SetRotation(Vector3 vRotation);
	Vector3 GetRotation();

	void SetPhisicsMaterial(Material * vmat);
	Material* GetPhisicsMaterial();

	vec4 GetForward();

	void Update();
};

