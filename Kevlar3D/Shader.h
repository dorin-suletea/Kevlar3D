#pragma once
#include <iostream>
#include "GLIncludes.h"
#include "ShaderTypes.h"
using namespace std;

class Shader{
private : 
	std::string fileLocation;
	ShaderTypes shaderType;

public :
	Shader(string vFileLocation,ShaderTypes vShaderType);
	Shader();
	const string GetSrc();
	GLuint CompileShader();
};