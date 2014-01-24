#include "GameObject.h"
using namespace std;




GameObject::GameObject(string vname)
	:name(vname){
	vertexBufferPtr = -1;
	vertexOffsetPtr = -1;
	position = Vector3(0.0f,0.0f,0.0f);
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
	////set the data into our buffer
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vector3)*vecSize,vertices,GL_STATIC_DRAW);

	//doubleckeck for errors
	GLenum err = glGetError();

	if (0 != err){
		Log::GetInstance()->LogErr("GameObject " + name +" failed to set mesh vertices "+ to_string(err));
	}
	return 0 ;
}

void 
GameObject::SetMaterial(Material* vmat){
	Log::GetInstance()->SetContext("GameObject");

	material = vmat;
	//setting pointer to offset shader attributes
	vertexOffsetPtr = glGetUniformLocation(material->GetShaderProgram(), "Offset");

	if (-1 == vertexOffsetPtr){
		Log::GetInstance()->LogErr("Can not obtain Offset shader attribute, make sure material " +material->GetName() + "is offsetable ; game object "+name);
	}
}

void 
GameObject::SetPosition(Vector3 vPosition){
	positionDirty = true;
	position = vPosition; 
}

string 
GameObject::GetName(){
	return name;
}

Vector3 
GameObject::GetPosition(){
	return position;
}

void 
GameObject::updatePosition(){
	if (NULL == material || -1 == vertexOffsetPtr){
		Log::GetInstance()->LogErr("Position can not be updated , no material reference was set for game object, "+name +" or material does not contain vertex_position_shader");
		positionDirty = false;
		return;
	}
	positionDirty = false;
	glUniform3f(vertexOffsetPtr,position.x,position.y,position.z);
}


void 
GameObject::Draw(){
	material->Use();
	if (positionDirty){
		updatePosition();
	}
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferPtr);
	////	//tell gl how to parse tha data from our buffer (Vector3 vertices[])
	////	//first param = shader parameter index , set this item for the parameter 0 in the fixed_function pipeline
	////	//second+third param = we passed a Vecto3 , pen GL must interpret the object , so Gl must know that Vector 3 is composed by 3 floats
	////	//forth param = normalize vecor?
	////	//fifth param = stride : the size of the structure passwd in bytes
	////	//sixth param = offset : the byte offset in our object (in case it has fields opn gl does not care about)
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableVertexAttribArray(0);
}

