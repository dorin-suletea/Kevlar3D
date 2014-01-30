#pragma once
#include "GLIncludes.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Log.h"
using namespace std;

class Material
{
private:	
	string name;
	GLuint shaderProgram;
	vector<Shader> shaderList;

public:
	Material(string name);
	Material();
	~Material(void);
	void Compile();
	void AddShader(Shader vshader);
	void Use();
	const GLuint GetShaderProgram();
	string GetName();
};

