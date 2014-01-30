#include "Transform.h"
#include <glm/gtx/euler_angles.hpp>

Transform::Transform(Material * vPhisicsMaterial):
	scale(Vector3(1,1,1)),
	position(Vector3(1,1,1)),
	positionUniformPtr(-1),
	scaleUniformPtr(-1),
	rotationEulerAngles(Vector3(0,0,0)),
	forward(vec4(1,0,0,1)){

	SetPhisicsMaterial(vPhisicsMaterial);
}


Transform::~Transform(void)
{
}

void 
Transform::SetPhisicsMaterial(Material* vmat){
	phisicsMaterial = vmat;

	positionUniformPtr = glGetUniformLocation(phisicsMaterial->GetShaderProgram(), "Offset");
	scaleUniformPtr = glGetUniformLocation(phisicsMaterial->GetShaderProgram(), "Scale");
	rotationUniformPtr = glGetUniformLocation(phisicsMaterial->GetShaderProgram(), "Rotation");
	
	if (-1 == positionUniformPtr){
		Log::GetInstance()->LogErr("Can not obtain Offset shader attribute, make sure material " +phisicsMaterial->GetName() + "is offsetable ");
	}

	if (-1 == scaleUniformPtr){
		Log::GetInstance()->LogErr("Can not obtain Scale shader attribute, make sure material " +phisicsMaterial->GetName() + "is Scalable");
	}

	if (-1 == rotationUniformPtr){
		Log::GetInstance()->LogErr("Can not obtain Rotation shader attribute, make sure material " +phisicsMaterial->GetName() + "is Rotable ");
	}
	
	isDirty = true;
}


void
Transform::SetPosition(Vector3 vPosition){
	Log::GetInstance()->SetContext("Transform");

	position = vPosition;
	isDirty = true;
}

Vector3 
Transform::GetPosition(){
	return position;
}

Material*
Transform::GetPhisicsMaterial(){
	return phisicsMaterial;
}

void 
Transform::SetScale(Vector3 vscale){
	scale = vscale;
	isDirty = true;

}

void 
Transform::SetScale(float vscale){
	SetScale(Vector3(vscale,vscale,vscale));
	isDirty = true;
}

void 
Transform::SetRotation(Vector3 vRotation){
	rotationEulerAngles = vRotation;
	isDirty = true;
}

vec4 
Transform::GetForward(){
	return forward;
}

Vector3 
Transform::GetRotation(){
	return rotationEulerAngles;
}

void 
Transform::updatePosition(){
	if (NULL == phisicsMaterial){
		Log::GetInstance()->LogErr("Phisics material was not set on the this transform , can not update position");
		return;
	}
	if  (-1 == positionUniformPtr){
		Log::GetInstance()->LogErr("Phisics material has not Position uniform : vertex_position_shader");
		return;
	}
	glUniform4f(positionUniformPtr,position.x,position.y,position.z,1);
}

void 
Transform::updateScale(){
	if (NULL == phisicsMaterial){
		Log::GetInstance()->LogErr("Phisics material was not set on the this transform , can not update scale");
		return;
	}
	if  (-1 == scaleUniformPtr){
		Log::GetInstance()->LogErr("Phisics material has not Scale uniform : vertex_position_shader");
		return;
	}
	glUniform4f(scaleUniformPtr,scale.x,scale.y,scale.z,1);;
}




void 
Transform::updateRotation(){

	if (NULL == phisicsMaterial){
		Log::GetInstance()->LogErr("Phisics material was not set on the this transform , can not update rotation");
		return;
	}
	if  (-1 == rotationUniformPtr){
		Log::GetInstance()->LogErr("Phisics material has not Rotation uniform : vertex_position_shader");
		return;
	}
	// create the rotation matrix (note that y and x are reversed , il write when i know why this was needed)
	// note THIS SHIT EXPECTS RADIANS
	//this->rotationMatrix
	rotationMatrix = glm::eulerAngleYXZ(glm::radians(rotationEulerAngles.y),glm::radians(rotationEulerAngles.x),glm::radians(rotationEulerAngles.z));
	//rotMatrix * constant absolute forward vector 
	forward = rotationMatrix * vec4(0,0,1,1);

	glUniformMatrix4fv(rotationUniformPtr, 1, GL_FALSE, &rotationMatrix[0][0]);
}





void
Transform::Update(){
	if (isDirty){
		updatePosition();
		updateScale();
		updateRotation();
		isDirty = false;
	}
}