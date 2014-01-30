#include "Material.h"


Material::Material(string vname)
	:name(vname){
	shaderProgram=-1;
}

Material::Material(){
	Material("Unknown material");
}

Material::~Material(void)
{
}

void
Material::AddShader(Shader vshader){
	shaderList.push_back(vshader);
	Log::GetInstance()->SetContext("Material");
}


void
Material::Compile(){
	Log::GetInstance()->SetContext("Material");
	Log::GetInstance()->LogInfo("Initializing Material");

	//if material is reused
	if (-1 != shaderProgram){
		Log::GetInstance()->LogInfo("Shader program for material "+ name +" already exists , cleaning it up");
		glDeleteProgram(shaderProgram);
	}
	
	//creation
	shaderProgram = glCreateProgram();
	GLuint shaderHdl = -1 ;

	for (Shader sh : shaderList){
		shaderHdl = sh.CompileShader();
		if (-1 != shaderHdl){
			glAttachShader(shaderProgram,shaderHdl);
		}
	}
	glLinkProgram(shaderProgram);



	//validation
	GLint linkOk = GL_FALSE;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&linkOk);
	if (linkOk==GL_FALSE){
		int infoLogLen;
		glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&infoLogLen);
		char* log = new char[infoLogLen];
		glGetProgramInfoLog(shaderProgram,sizeof(log),&infoLogLen,log);
		Log::GetInstance()->LogErr("Fail linking with error "+string(log));
	}

	glValidateProgram(shaderProgram);
	GLint programValid = GL_FALSE;
	glGetProgramiv(shaderProgram,GL_VALIDATE_STATUS,&programValid);
	if (programValid==GL_FALSE){
		int infoLogLen;
		glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&infoLogLen);
		char* log = new char[infoLogLen];
		glGetProgramInfoLog(shaderProgram,sizeof(log),&infoLogLen,log);
		Log::GetInstance()->LogErr("Fail validationg  with error "+string(log));
	}
}

void
Material::Use(){
	Log::GetInstance()->SetContext("Material");
	if (-1 == shaderProgram){
		Log::GetInstance()->LogErr("Material not compiled , have you forgot to call .Compile()?");
	}
	glUseProgram(shaderProgram);
}


const GLuint
Material::GetShaderProgram(){
	return shaderProgram;
}

string
Material::GetName(){
	return name;
}
