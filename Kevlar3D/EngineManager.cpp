#include "EngineManager.h"

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


EngineManager::EngineManager()
{
}

EngineManager::~EngineManager(void)
{
}

/*static*/
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
EngineManager::Render(void)const
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//ShaderInfo shaders[] = {
	//	{ GL_VERTEX_SHADER, "triangles.vert" },
	//	{ GL_FRAGMENT_SHADER, "triangles.frag" },
	//	{ GL_NONE, NULL }
	//};



	//shaderProgram = InitShader("beelsebob.vert",  "beelsebob.frag", "fragColour");
	//positionUniform = glGetUniformLocation(shaderProgram, "p");
	//if (positionUniform < 0) {
	//	cerr << "Shader did not contain the 'p' uniform."<<endl;
	//}
	//colourAttribute = glGetAttribLocation(shaderProgram, "colour");
	//if (colourAttribute < 0) {
	//	cerr << "Shader did not contain the 'colour' attribute." << endl;
	//}
	//positionAttribute = glGetAttribLocation(shaderProgram, "position");
	//if (positionAttribute < 0) {
	//	cerr << "Shader did not contain the 'position' attribute." << endl;
	//}


	
    //glUseProgram(shaderProgram);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
	//glutSwapBuffers();
}
	

void 
EngineManager::HandleKeypress(unsigned char key, int x, int y)
{

}

//Handlers
//************************************************

//************************************************
//Business Logic
void 
EngineManager::Start(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(400, 400); 
	glutCreateWindow("Basic Shapes - programming-technique.blogspot.com");

	glutDisplayFunc(GlobalRenderHandler);
	//glutKeyboardFunc(GlobalKeyHandler);
	glutReshapeFunc(GlobalResizeHandler);




	glewExperimental = GL_TRUE;// Added because of http://openglbook.com/glgenvertexarrays-access-violationsegfault-with-glew/

	GLint glewStartCode = glewInit();
	if (glewInit() != GLEW_OK) {
		Log::GetInstance()->LogErr(glewGetErrorString(glewStartCode));
	}

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();


}
//Logic
//************************************************
