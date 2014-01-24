#include "EngineManager.h"
#include "Shader.h"
#include "Vector.h"
#include "Material.h"
#include "GameObject.h"


//************************************************
//CallbackDelegates for GL_Manager

void 
GlobalRenderHandler()
{
	EngineManager::GetInstance()->Render();
}

void 
GlobalKeyHandler(unsigned char key, int x, int y)
{
	EngineManager::GetInstance()->HandleKeypress(key,  x,  y);
}

void
GlobalResizeHandler(int newW,int newH){
	EngineManager::GetInstance()->HandleResize(newW,newH);
}
//
//************************************************


//************************************************
//Construction
std::shared_ptr<EngineManager>  EngineManager::s_instance = NULL;

EngineManager::EngineManager(){
	gameObjectList = new vector<GameObject>();
}

EngineManager::~EngineManager(void){
	delete gameObjectList;
}

std::shared_ptr<EngineManager>
EngineManager::GetInstance()
{
	if (NULL==EngineManager::s_instance)
		EngineManager::s_instance=std::shared_ptr<EngineManager>(new EngineManager);

	return EngineManager::s_instance;
}
//Construction
//************************************************

//************************************************
//Handlers
void 
EngineManager::HandleResize(int newW,int newH)
{
	//glViewport(0, 0, newW, newH);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////TODO hardcode implementation 
	//gluPerspective(45.0,(double)newW / (double)newH,1.0, 200.0);  
}

	
void 
EngineManager::HandleKeypress(unsigned char key, int x, int y)
{
	//Log::GetInstance()->LogInfo("Key pressed");

	Vector3 delta = Vector3(0.1f , 0.0f , 0.0f);
	for(std::vector<GameObject>::iterator it = gameObjectList->begin(); it != gameObjectList->end(); ++it){
		it->SetPosition(it->GetPosition()+delta);
	}
	glutPostRedisplay();
}

//Handlers
//************************************************

//************************************************
//Business Logic
void 
EngineManager::Start(int argc, char** argv){
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//if core version is above 3.2 fixed pipeline wont work
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(400, 400); 
	glutInitWindowPosition(100,100);


	glutCreateWindow("Basic Shapes - programming-technique.blogspot.com");

	glutDisplayFunc(&GlobalRenderHandler);
	glutKeyboardFunc(&GlobalKeyHandler);

	glewExperimental = GL_TRUE;// Added because of http://openglbook.com/glgenvertexarrays-access-violationsegfault-with-glew/
	glewInit();

	GLenum err = -1;
	err = glGetError();

	glClearColor(0,0,0,0);

	EngineManager::GetInstance()->Init();
	glutMainLoop();
}



void	
EngineManager::Init(){
	//make the default material
	Material *defaultMaterial = new Material("Default material");
	Shader vertShader =   Shader("vertex_position_shader.txt",ShaderTypes::VERTEX_SHADER);
	Shader fragShader =   Shader("fragment_shader.txt",ShaderTypes::FRAGMENT_SHADER);
	
	defaultMaterial->AddShader(vertShader);
	defaultMaterial->AddShader(fragShader);
	defaultMaterial->Compile();

	////make the game object
	vector<Vector3> triangle1Points = vector<Vector3>();
	triangle1Points.push_back(Vector3(-0.6f , -0.6f , 0.0f));
	triangle1Points.push_back(Vector3( 0.0f ,  0.6f , 0.0f));
	triangle1Points.push_back(Vector3(0.6f , -0.6f , 0.0f));

	GameObject triangle1 = GameObject("Triangle_1");
	triangle1.SetMeshVertices(triangle1Points);
	triangle1.SetMaterial(defaultMaterial);
	triangle1.SetPosition(Vector3(0.0f , 0.0f , 0.0f));
	gameObjectList->push_back(triangle1);
}


void
EngineManager::Render(void)const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(std::vector<GameObject>::iterator it = gameObjectList->begin(); it != gameObjectList->end(); ++it){
		it->Draw();
	}

	glutSwapBuffers();
	glDisableVertexAttribArray(0);
}








//Logic
//************************************************



//======================================================
//BACKUPS

//void
//EngineManager::Render(void)const
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	////something with shaders
//	//glEnableVertexAttribArray(0);
//	////you can remove the bind buffer from setup
//	//if (!seq)
//	//{
//	//	glBindBuffer(GL_ARRAY_BUFFER,buffer_handlers_1);
//	//	seq = true;
//	//}else
//	//{
//	//	glBindBuffer(GL_ARRAY_BUFFER,buffer_handlers_2);
//	//	seq = false;
//	//}
//
//	////tell gl how to parse tha data from our buffer (Vector3 vertices[])
//	////first param = shader parameter index , set this item for the parameter 0 in the fixed_function pipeline
//	////second+third param = we passed a Vecto3 , pen GL must interpret the object , so Gl must know that Vector 3 is composed by 3 floats
//	////forth param = normalize vecor?
//	////fifth param = stride : the size of the structure passwd in bytes
//	////sixth param = offset : the byte offset in our object (in case it has fields opn gl does not care about)
//	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
//
//	////draw
//	//glDrawArrays(GL_TRIANGLES,0,3);
//
//
//	////Log::GetInstance()->LogErr(buffer_handlers);
//
//
//
//	//glutSwapBuffers();
//	//glDisableVertexAttribArray(0);
//
//
//
//
//	//ShaderInfo shaders[] = {
//	//	{ GL_VERTEX_SHADER, "triangles.vert" },
//	//	{ GL_FRAGMENT_SHADER, "triangles.frag" },
//	//	{ GL_NONE, NULL }
//	//};
//
//
//
//	//shaderProgram = InitShader("beelsebob.vert",  "beelsebob.frag", "fragColour");
//	//positionUniform = glGetUniformLocation(shaderProgram, "p");
//	//if (positionUniform < 0) {
//	//	cerr << "Shader did not contain the 'p' uniform."<<endl;
//	//}
//	//colourAttribute = glGetAttribLocation(shaderProgram, "colour");
//	//if (colourAttribute < 0) {
//	//	cerr << "Shader did not contain the 'colour' attribute." << endl;
//	//}
//	//positionAttribute = glGetAttribLocation(shaderProgram, "position");
//	//if (positionAttribute < 0) {
//	//	cerr << "Shader did not contain the 'position' attribute." << endl;
//	//}
//
//
//	
//    //glUseProgram(shaderProgram);
//    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//    
//	//glutSwapBuffers();
//}





//void	
//EngineManager::Init(){
//	Vector3 vertices [3];
//	vertices[0] = Vector3(-0.6f,-0.6f,0.0f);
//	vertices[1] = Vector3(0,0.6f,0);
//	vertices[2] = Vector3(0.6f,-0.6f,0);
//	//generate 1 generic GPU buffer , and store its handler in buffer_handles array
//	glGenBuffers(1,&buffer_handlers_1);
//	//set the internal GL Array buffer point to our buffer
//	glBindBuffer(GL_ARRAY_BUFFER,buffer_handlers_1);
//	//set the data into our buffer
//	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//
//	Vector3 vertices2 [3];
//	vertices2[0] = Vector3(-0.1f,-0.1f,0.0f);
//	vertices2[1] = Vector3(0,0.1f,0);
//	vertices2[2] = Vector3(0.1f,-0.1f,0);
//
//	glGenBuffers(1,&buffer_handlers_2);
//	glBindBuffer(GL_ARRAY_BUFFER,buffer_handlers_2);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);
//
//
//
//
//	Material *defaultMaterial = new Material("Default material");
//	Shader vertShader =   Shader("vertex_shader.txt",ShaderTypes::VERTEX_SHADER);
//	Shader fragShader =   Shader("fragment_shader.txt",ShaderTypes::FRAGMENT_SHADER);
//	
//	defaultMaterial->AddShader(vertShader);
//	defaultMaterial->AddShader(fragShader);
//
//
//
//	defaultMaterial->Compile();
//	
//	//glGetAttribLocation(defaultMaterial->GetShaderProgram(),"Position");
//
//		GLint offset  = -1;
//	offset = glGetUniformLocation(defaultMaterial->GetShaderProgram(), "Offset");
//
//	Log::GetInstance()->LogInfo(to_string(offset));
//
//		defaultMaterial->Use();
//
//	glUniform3f(offset,0.9f,1.0f,0.0f);
//	
//
//
//
//
//
///*
//
//	GLuint shaderProg = glCreateProgram();
//
//
//
//	GLuint vertShaderHd = vertShader.CompileShader();
//	GLuint fragShaderHd = fragShader.CompileShader();
//
//
//
//	glAttachShader(shaderProg,vertShaderHd);
//	glAttachShader(shaderProg,fragShaderHd);
//
//
//	glLinkProgram(shaderProg);
//
//	
//	GLint linkOk = GL_FALSE;
//	glGetProgramiv(shaderProg,GL_LINK_STATUS,&linkOk);
//	if (linkOk==GL_FALSE){
//		Log::GetInstance()->LogInfo("Fail linking");
//	}
//
//	glValidateProgram(shaderProg);
//
//	GLint programValid = GL_FALSE;
//	glGetProgramiv(shaderProg,GL_VALIDATE_STATUS,&programValid);
//	if (programValid==GL_FALSE){
//		Log::GetInstance()->LogInfo("Fail validating");
//	}
//
//
//	glUseProgram(shaderProg);
//
//
//	Log::GetInstance()->LogErr("shader err pre 33333");
//	GLenum err = -1;
//	err = glGetError();
//	Log::GetInstance()->LogErr(err);
//*/
//
//
//	//GLsizei count = -1;
//	//GLuint shaderpt[4];
//
//	//glGetAttachedShaders(shaderProg,3,&count,shaderpt);
//	//Log::GetInstance()->LogErr(count);
//
//	//GLint id;
//	//glGetIntegerv(GL_CURRENT_PROGRAM,&id);
//	//Log::GetInstance()->LogErr(shaderProg);
//	//Log::GetInstance()->LogErr(id);
//
//
//
//
//	//GLenum err = glGetError();
//	//Log::GetInstance()->LogErr(err);
//	//glGetIntegerv(GL_CURRENT_PROGRAM,&amp;shaderProg);
//
//	 // /* compile the shader */
//  //GLuint shader = shaderCompileFromFile(type, filePath);
//  //if(shader != 0) {
//  //  /* attach the shader to the program */
//  //  glAttachShader(program, shader);
//
//  //  /* delete the shader - it won't actually be
//  //   * destroyed until the program that it's attached
//  //   * to has been destroyed */
//  //  glDeleteShader(shader);
//  //}
//}
////Logic
////************************************************
