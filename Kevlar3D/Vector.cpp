#include "Vector.h"

Vector3::Vector3(){
	x=0.0f;
	y=0.0f;
	z=0.0f;
};

Vector3::Vector3(float vx,float vy,float vz)
		:x(vx),y(vy),z(vz){};

Vector3 
Vector3::operator+(const Vector3& other){
	return Vector3(x+other.x,y+other.y,z+other.z);
}

ostream &operator<<(ostream& stream, const Vector3& item){
	stream<<"V3( "<<item.x<<" ; ";
	stream<<item.y<<" ; ";
	stream<<item.z<<" )"<<endl;
	return stream;
}