#include "ShaderFactory.h"
#include "Paths.h"


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

//BAD , refactor and remake all
GLuint
ShaderFactory::LoadShaders(Shader*  shaderInfo)
{
    GLuint program = glCreateProgram();
	GLuint shader = glCreateShader(shaderInfo->m_type);
	shaderInfo->m_shaderData=shader;
	const GLchar* source = &this->ReadFile(shaderInfo->m_filename)[0]; /*& and [0] converts from string to GlChar*/

    glShaderSource( shader, 1, &source, NULL );
	delete [] source;
	glCompileShader( shader );

        GLint compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            return 0;
        }

        glAttachShader( program, shader );
		glLinkProgram( program );

		GLint linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );
		if (!linked){
			 GLsizei len;
			 glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
			 GLchar* log = new GLchar[len+1];
			 glGetProgramInfoLog( program, len, &len, log );
			 Log::GetInstance()->LogErr(log);
			 delete [] log;
			 return 0;
		}


    return program;
}