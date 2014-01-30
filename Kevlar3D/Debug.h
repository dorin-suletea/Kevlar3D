#pragma once
#include "Material.h"
#include <memory>

class Debug
{
private:
	Material debugPhisicsMaterial;
	static const std::shared_ptr<Debug> instance;
	Debug(void);

public:
	static std::shared_ptr<Debug> GetInstance();
	~Debug(void);
	Material GetDebugMaterial();
	void Setup();

	//Util methods
	void DrawLine(Vector3 origin,Vector3 destination);
};

