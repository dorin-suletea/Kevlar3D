#include "Shader.h"
#include "Log.h"
#include <vector>
using namespace std;


Shader::Shader(std::string vFileLocation,ShaderTypes vShaderType)
	:fileLocation(vFileLocation),shaderType(vShaderType){};


Shader::Shader(){};

const string 
Shader::GetSrc()
{
	Log::GetInstance()->SetContext("Shader");
	std::ifstream in(SHADER_PATH+ this->fileLocation, ios::in | ios::binary);
	if (!in){
		Log::GetInstance()->LogErr("Read file [" +SHADER_PATH + this->fileLocation + "] failed");
		return "";
	}
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
};


GLuint
Shader::CompileShader(){
	Log::GetInstance()->SetContext("Shader");

	//shader created
	GLuint shaderID = glCreateShader(this->shaderType);
	if (0 != shaderID){
		Log::GetInstance()->LogInfo("Shader alloc mem ok" );
	} else{
		Log::GetInstance()->LogInfo("Shader alloc mem failed" );
	}

	//shader set source
	string shaderSource = this->GetSrc();
	const char* shaderSrcCharPtr = shaderSource.c_str();
	Log::GetInstance()->LogInfo("Compiling shader "+this->fileLocation);
	glShaderSource( shaderID, 1, &shaderSrcCharPtr, NULL );

	//compile
	glCompileShader(shaderID);

	//checks
	GLint compilationOk = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationOk);
	if (GL_TRUE == compilationOk){
		Log::GetInstance()->LogInfo("Shader compiled ok");
	}else{
		Log::GetInstance()->LogErr("Shader not compiled");
		Log::GetInstance()->LogInfo("Shader about to compile " + shaderSource);
		int logLength = -1;
		Log::GetInstance()->LogErr(logLength);
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		


		vector<char> errorMessage(logLength);

		glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
		Log::GetInstance()->LogErr(&errorMessage[0]);
		return -1;
	}
	return shaderID;
}