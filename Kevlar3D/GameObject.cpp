#include "GameObject.h"
#include "Debug.h"
using namespace std;




GameObject::GameObject(string vname)
	:name(vname){
	vertexBufferPtr = -1;
	vetexCount = -1;
	debugMaterial = NULL;
	animator = NULL;
}

GameObject::GameObject(){
	name= "Unnamed";
}

GameObject::~GameObject(){
}

int
GameObject::SetMeshVertices(vector<Vector3> meshVertices){
	Log::GetInstance()->SetContext("GameObject");

	//clean pervious buffer
	if (-1 != vertexBufferPtr){
		const GLuint my_array[] = { vertexBufferPtr };
		glDeleteBuffers(1,my_array);
	}

	const int vecSize = meshVertices.size();
	Vector3 * vertices = &meshVertices[0];

	////generate 1 generic GPU buffer , and store its handler in buffer_handles array
	glGenBuffers(1,&vertexBufferPtr);
	if (-1 == vertexBufferPtr){
		Log::GetInstance()->LogErr("Failed to allocate gl vertex buffer for game object"+name);
		return -1;
	}

	////set the internal GL Array buffer point to our buffer
	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferPtr);
	this->vetexCount = vecSize;
	////set the data into our buffer
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vector3)*vecSize,vertices,GL_STATIC_DRAW);

	//doubleckeck for errors
	GLenum err = glGetError();

	if (0 != err){
		Log::GetInstance()->LogErr("GameObject " + name +" failed to set mesh vertices "+ to_string(err));
	}
	return 0 ;
}

string 
GameObject::GetName(){
	return name;
}

Transform* 
GameObject::GetTransform(){
	return transform;
}

void
GameObject::SetTransform(Transform* vTransform){
	transform = vTransform;
}

void 
GameObject::SetDebugMaterial(Material *vMaterial){
	debugMaterial = vMaterial;
}

void
GameObject::SetAnimator(Animator* vanimator){
	animator = vanimator;
}


Animator* 
GameObject::GetAnimator(){
	return animator;
}

void 
GameObject::Update(){
	if (NULL!=animator && animator->HasActiveAnimations()){
		animator->Update();
		SetMeshVertices(animator->GetMeshVertices());
	}
	transform->GetPhisicsMaterial()->Use();
	transform->Update();
}

void 
GameObject::Draw(){
	//Log::GetInstance()->LogErr(to_string(transform->GetForward().x));
	//Log::GetInstance()->LogErr(transform->GetForward().y);
	//Log::GetInstance()->LogErr(transform->GetForward().z);
	Debug::GetInstance()->DrawLine(transform->GetPosition(),Vector3(transform->GetForward().x, transform->GetForward().y,transform->GetForward().z));
	transform->GetPhisicsMaterial()->Use();


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferPtr);
	////	//tell gl how to parse tha data from our buffer (Vector3 vertices[])
	////	//first param = shader parameter index , set this item for the parameter 0 in the fixed_function pipeline
	////	//second+third param = we passed a Vecto3 , pen GL must interpret the object , so Gl must know that Vector 3 is composed by 3 floats
	////	//forth param = normalize vecor?
	////	//fifth param = stride : the size of the structure passwd in bytes
	////	//sixth param = offset : the byte offset in our object (in case it has fields opn gl does not care about)
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glDrawArrays(GL_TRIANGLES,0,vetexCount);
	glDisableVertexAttribArray(0);
}

