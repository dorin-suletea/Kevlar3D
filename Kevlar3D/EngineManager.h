#pragma once
#include <memory>
#include "Log.h"



 

class EngineManager
{
private:
	std::shared_ptr<EngineManager> static		s_instance;
												EngineManager(void);
public:

												~EngineManager(void);
	void virtual								Start(int argc, char** argv);
	std::shared_ptr<EngineManager>	static		GetInstance();
	void virtual								HandleResize(int newW,int newH);
	void virtual								HandleKeypress(unsigned char key, int x, int y);
	void virtual								Render(void)const;
};

