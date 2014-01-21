#include "ShaderFactory.h"
#include "Paths.h"
#include <vector>



using namespace std;

ShaderFactory::ShaderFactory(void)
{
}


ShaderFactory::~ShaderFactory(void)
{
}

const std::string 
ShaderFactory::ReadFile(std::string const &fileName)
{
	Log::GetInstance()->SetContext("ShaderFactory");
	std::ifstream in(SHADER_PATH+fileName, ios::in | ios::binary);
	if (!in){
		Log::GetInstance()->LogErr("Read file [" +SHADER_PATH+fileName+ "] failed");
		return "";
	}
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
}


GLuint
ShaderFactory::CompileShader(ShaderTypes shaderType,std::string filename){
	Log::GetInstance()->SetContext("ShaderFactory");

	//shader created
	GLuint shaderID = glCreateShader(shaderType);
	if (0 != shaderID){
		Log::GetInstance()->LogInfo("Shader created" );
	} else{
		Log::GetInstance()->LogInfo("Shader creation failed" );
	}

	//shader set source
	std::string shaderSource = ReadFile(filename);
	const char* shaderSrcCharPtr = shaderSource.c_str();
	Log::GetInstance()->LogInfo("Shader about to compile " + shaderSource);
	glShaderSource( shaderID, 1, &shaderSrcCharPtr, NULL );

	//compile
	glCompileShader(shaderID);

	
    // Check Vertex Shader
	//is the shader compiled OK?
	GLint compilationOk = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationOk);
	if (GL_TRUE == compilationOk){
		Log::GetInstance()->LogInfo("Shader compiled ok");
	}else{
		Log::GetInstance()->LogErr("Shader not compiled");
		int logLength = -1;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> errorMessage(logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
		Log::GetInstance()->LogErr(&errorMessage[0]);
		return -1;
	}
	return shaderID;
}



//BAD , refactor and remake all
//GLuint
//ShaderFactory::LoadShaders(Shader*  shaderInfo)
//{
//    GLuint program = glCreateProgram();
//	GLuint shader = glCreateShader(shaderInfo->m_type);
//	shaderInfo->m_shaderData=shader;
//	const GLchar* source = &this->ReadFile(shaderInfo->m_filename)[0]; /*& and [0] converts from string to GlChar*/
//
//    glShaderSource( shader, 1, &source, NULL );
//	delete [] source;
//	glCompileShader( shader );
//
//        GLint compiled;
//        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
//        if ( !compiled ) {
//            return 0;
//        }
//
//        glAttachShader( program, shader );
//		glLinkProgram( program );
//
//		GLint linked;
//		glGetProgramiv( program, GL_LINK_STATUS, &linked );
//		if (!linked){
//			 GLsizei len;
//			 glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
//			 GLchar* log = new GLchar[len+1];
//			 glGetProgramInfoLog( program, len, &len, log );
//			 Log::GetInstance()->LogErr(log);
//			 delete [] log;
//			 return 0;
//		}
//    return program;
//}