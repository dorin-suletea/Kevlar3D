#pragma once
#include <memory>
#include "GameObject.h"
#include <vector>
using namespace std;

 

class EngineManager
{
private:
	shared_ptr<EngineManager>	static			s_instance;
												EngineManager(void);
	vector<GameObject>*							gameObjectList;
public:

												~EngineManager(void);
	void virtual								Start(int argc, char** argv);
	shared_ptr<EngineManager>		static		GetInstance();
	void virtual								HandleResize(int newW,int newH);
	void virtual								HandleKeypress(unsigned char key, int x, int y);
	void virtual								Render(void)const;
	void										Init();
};

