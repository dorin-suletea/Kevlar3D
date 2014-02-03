#pragma once
#include "Material.h"
#include <vector>
#include "Vector.h"
#include "ResourceLoader.h"

class EngineHelper
{
public:
	EngineHelper(void);
	~EngineHelper(void);

	static Material*			MakeDefaultMaterial();
	static Material*			MakeDebugMaterial();
	static std::vector<Vector3> LoadDravenVerts();
	static std::vector<Vector3> LoadCubeVerts();
};

