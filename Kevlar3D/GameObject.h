#pragma once
#include "Vector.h"
#include <vector>
#include "Material.h"

using namespace std;

class GameObject
{
private:
	Vector3 position;
	Material* material;
	string name;
	GLuint vertexBufferPtr;
	GLuint vertexOffsetPtr;

	//if position is updated positionDirty=true; on the next draw call if positionDirty the vector offset is updated and positionDirty=false, 
	bool positionDirty;
	void updatePosition();
public:
	GameObject(string vname);
	GameObject();
	~GameObject(void);


	void Draw();


	void SetMaterial(Material* vmat);
	int	 SetMeshVertices(vector<Vector3> meshVertices);
	void SetPosition(Vector3 vPosition);
	string GetName();
	Vector3 GetPosition();

};

