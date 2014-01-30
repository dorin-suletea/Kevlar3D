#pragma once
#include "Vector.h"
#include <vector>
#include "Material.h"
#include "Transform.h"

using namespace std;

class GameObject
{
private:
	string name;
	GLuint vertexBufferPtr;
	GLsizei vetexCount;
	Transform* transform;
	Material* debugMaterial;

public:
	GameObject(string vname);
	GameObject();
	~GameObject(void);


	void Draw();
	int	 SetMeshVertices(vector<Vector3> meshVertices);
	string GetName();
	Transform* GetTransform();
	void SetTransform(Transform* vTransform);

	void SetDebugMaterial(Material *vMaterial);
};

