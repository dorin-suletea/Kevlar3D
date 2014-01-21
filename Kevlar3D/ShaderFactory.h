#pragma once
#include "Log.h"
#include "GLIncludes.h"
#include "ShaderTypes.h"

//typedef struct {
//    const GLenum 			m_type;
//    const char*				m_filename;
//    GLuint				    m_shaderData;
//} Shader;

class ShaderFactory
{
private:
	

public:
	ShaderFactory(void);
	~ShaderFactory(void);

	const std::string						ReadFile(std::string const &relativePath);
	GLuint                                  CompileShader(ShaderTypes shaderType,std::string filename);
};

