#include "EngineManager.h"
#include "Shader.h"
#include "Vector.h"
#include "Material.h"
#include "GameObject.h"
#include "glm\mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceLoader.h"
#include "Debug.h"
#include "EngineHelper.h"
#include "MD2Animation.h"

//************************************************
//CallbackDelegates for GL_Manager

void 
GlobalRenderHandler()
{
	EngineManager::GetInstance()->Render();
}

void
GlobalTimer(int timeValue)
{
	EngineManager::GetInstance()->Timer(timeValue);
}

void 
GlobalKeyHandler(unsigned char key, int x, int y)
{
	EngineManager::GetInstance()->HandleKeypress(key,  x,  y);
}

void 
GlobalKeyReleaseHandler(unsigned char key, int x, int y)
{
	EngineManager::GetInstance()->HandleKeyRelease(key,  x,  y);
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
EngineManager::Timer(int timeValue){
	for(std::vector<GameObject>::iterator it = gameObjectList->begin(); it != gameObjectList->end(); ++it){
		it->Update();
	}
	glutTimerFunc( 10,&GlobalTimer , 0);
	glutPostRedisplay();
}

void 
EngineManager::HandleResize(int newW,int newH)
{
	//glViewport(0, 0, newW, newH);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////TODO hardcode implementation 
	//gluPerspective(45.0,(double)newW / (double)newH,1.0, 200.0);  
}

bool isMoving = false;
	
void 
EngineManager::HandleKeypress(unsigned char key, int x, int y)
{
	Vector3 deltaMovement = Vector3(0.1f , 0.0f , 0.0f);

	//for(std::vector<GameObject>::iterator it = gameObjectList->begin(); it != gameObjectList->end(); ++it){
		GameObject it = gameObjectList->at(0);
		Animator* anim;
		float movementSpeed = 0.01;
		vec4 delta;
		Vector3 pos;
		switch(key)
		{
		case 'a': 
				it.GetTransform()->SetRotation(it.GetTransform()->GetRotation()+Vector3(0.0,1,0.0));
				break;
		case 'd': 
				it.GetTransform()->SetRotation(it.GetTransform()->GetRotation()+Vector3(0.0,-1,0.0));
				break;
		case 'w': 
			pos = it.GetTransform()->GetPosition();
			delta = it.GetTransform()->GetForward()*movementSpeed;
			it.GetTransform()->SetPosition(Vector3(pos.x+delta.x,pos.y+delta.y,pos.z+delta.z));
			anim = it.GetAnimator();
			if (NULL != anim){
				anim->PlayAnimation("draven_run");
			}
			break;
		default :
			break;
		}
	//}
	glutPostRedisplay();
}


void EngineManager::HandleKeyRelease(unsigned char key, int x, int y){
	Animator* anim;
	GameObject it = gameObjectList->at(0);
	switch(key)
		{
		case 'w':
			anim = it.GetAnimator();
			if (NULL != anim){
				anim->StopAnimation("draven_run");
			}
			break;
		default :
			break;
		}
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
	glutInitContextVersion(3, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(1300, 800); 
	glutInitWindowPosition(100,100);


	glutCreateWindow("Basic Shapes - programming-technique.blogspot.com");

	glutDisplayFunc(&GlobalRenderHandler);
	glutKeyboardFunc(&GlobalKeyHandler);
	glutKeyboardUpFunc(&GlobalKeyReleaseHandler);
	glutTimerFunc (1, &GlobalTimer,0);

	glewExperimental = GL_TRUE;// Added because of http://openglbook.com/glgenvertexarrays-access-violationsegfault-with-glew/
	glewInit();

	//speeds up by not rendering object's back but!!
	//all triangles must be defined clockwise or they wont be visible 
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);


	GLenum err = -1;
	err = glGetError();

	glClearColor(0,0,0,0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluLookAt(-15.0,-2.0,-1.0,0.4,0,0,0,0,0);
	//gluLookat(1/dist, 1/dist, 1/dist, 0,0,0, 0,1,0);
	EngineManager::GetInstance()->Init();
	glutMainLoop();
}


glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 3.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 View       = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
);
glm::mat4 Model      = glm::mat4(1.0f);  // Changes for each model !
// Our ModelViewProjection : multiplication of our 3 matrices
glm::mat4 MVP        = ProjectionMatrix * View * Model; // Remember, matrix multiplication is the other way ar



void	
EngineManager::Init(){
	//initialize the debug shaders
	Debug::GetInstance()->Setup();

	//make materials
	Material *defaultMaterial = EngineHelper::MakeDefaultMaterial();
	Material *debug = EngineHelper::MakeDebugMaterial();

	//load draven
	vector<Vector3> dravenVerts = EngineHelper::LoadDravenVerts();
	
	//load animations
	std::string dravenIdleAnimName = "draven_run";
	MD2Animation *dravenIdle  = new MD2Animation(dravenIdleAnimName); 
	dravenIdle->Load("C:/Users/GameDEV/Desktop/runing_draven_md2_v2.md2");
	MD2Animation *randomCrap  = new MD2Animation("rd"); 
	randomCrap->Load("C:/Users/GameDEV/Desktop/runing_draven_md2_v2.md2");

	Animator* animator = new Animator();
	animator->AddAnimation(dravenIdle);
	animator->AddAnimation(randomCrap);



	//assemble
	Transform* transformDraven = new Transform(defaultMaterial);
	GameObject dravenGo = GameObject("Draven");
	dravenGo.SetDebugMaterial(debug);
	dravenGo.SetTransform(transformDraven);
	dravenGo.SetMeshVertices(dravenVerts);
	dravenGo.SetAnimator(animator);

	//set data
	dravenGo.GetTransform()->SetPosition(Vector3(0.5f ,-0.5 , 0.3f));
	dravenGo.GetTransform()->SetScale(0.005);
	dravenGo.GetTransform()->SetRotation(Vector3(0,0,0));




	gameObjectList->push_back(dravenGo);

	GLuint MatrixID = glGetUniformLocation(defaultMaterial->GetShaderProgram(), "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);




	//obj.Load("C:/Users/GameDEV/Desktop/md2loader/hueteotl/tris.md2");
	//obj.md2WriteLog("C:/Users/GameDEV/Desktop/md2loader/hueteotl/tris.md2");

	// and in case you want to change to a particular frame simply do

	//obj.SetFrame(3); // base zero. 
	//obj.Draw();


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
