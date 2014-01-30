#include "Debug.h"




const std::shared_ptr<Debug>
	Debug::instance = std::shared_ptr<Debug>(new Debug());


Debug::Debug(void){
}

Material
Debug::GetDebugMaterial(){
	return debugPhisicsMaterial;
}

void
Debug::Setup(){
	debugPhisicsMaterial = Material("Debug phisics material");
	Shader debugVertShader =   Shader("vertex_shader.txt",ShaderTypes::VERTEX_SHADER);
	Shader debugFragShader =   Shader("fragment_shader.txt",ShaderTypes::FRAGMENT_SHADER);

	debugPhisicsMaterial.AddShader(debugVertShader);
	debugPhisicsMaterial.AddShader(debugFragShader);
	debugPhisicsMaterial.Compile();
}

std::shared_ptr<Debug>
Debug::GetInstance()
{
	return Debug::instance;
}


Debug::~Debug(void){
}

void 
Debug::DrawLine(Vector3 origin,Vector3 destination){
	debugPhisicsMaterial.Use();
	glBegin(GL_LINES);
		glVertex3f(origin.x,origin.y,origin.z);
		glVertex3f(destination.x, destination.y,destination.z);
	glEnd();
}

