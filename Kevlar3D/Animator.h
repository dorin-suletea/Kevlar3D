#pragma once
#include <vector>
#include "MD2Animation.h"
#include <string>
#include "Log.h"
using namespace std;

class Animator
{

private:
	vector<MD2Animation*> animationsAll;
	vector<MD2Animation*> animationsInProgress;
private:
	MD2Animation*		 getAnimationByName(string animName);


public:
	Animator(void);
	~Animator(void);

public:
	vector<string>		 GetAllAnimationNames();
	void				 PlayAnimation(string animName);
	void				 StopAnimation(string animName);
	void				 AddAnimation(MD2Animation *newAnim);
	void				 Update();
	vector<Vector3>		 GetMeshVertices();
	bool				 HasActiveAnimations();
};

