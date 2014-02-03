#include "Animator.h"


Animator::Animator(void)
{
	animationsAll = vector<MD2Animation*>();
	animationsInProgress = vector<MD2Animation*>();
}


Animator::~Animator(void)
{
}


vector<string>
Animator::GetAllAnimationNames(){
	vector<string> ret = vector<string>();
	for (int i=0; i<animationsAll.size();i++){
		ret.push_back(animationsAll.at(i)->GetAnimationName());
	}
	return ret;
}

void
Animator::AddAnimation(MD2Animation *newAnim){
	for (int i=0; i<animationsAll.size();i++){
		if (animationsAll.at(i)->GetAnimationName()==newAnim->GetAnimationName()){
			Log::GetInstance()->LogErr("Animation with same name already in the list , wont add"+newAnim->GetAnimationName());
			return;
		}
	}
	animationsAll.push_back(newAnim);
}

void	
Animator::PlayAnimation(string animName){
	for (int i=0; i<animationsInProgress.size();i++){
		if (animationsInProgress.at(i)->GetAnimationName()==animName){
				//Log::GetInstance()->LogErr("Animation already playing ,"+animName);
				return;
			}
	}
	animationsInProgress.push_back(getAnimationByName(animName));
}

void	
Animator::StopAnimation(string animName){
	int removeAt = -1;
	for (int i=0; i<animationsInProgress.size();i++){
		if (animationsInProgress.at(i)->GetAnimationName()==animName){
			removeAt = i;
			break;
		}
	}
	if (-1 != removeAt){
		animationsInProgress.erase(animationsInProgress.begin()+removeAt);
	}
}

bool
Animator::HasActiveAnimations(){
	return 0 != animationsInProgress.size();
}

MD2Animation*
Animator::getAnimationByName(string animName){
	for (int i=0; i<animationsAll.size();i++){
		if (animationsAll.at(i)->GetAnimationName() == animName){
			return animationsAll.at(i);
		}
	}
}

void Animator::Update(){
	for (int i=0; i<animationsInProgress.size();i++){
		animationsInProgress.at(i)->NextFrame();
	}
}

vector<Vector3>
Animator::GetMeshVertices(){
	return animationsInProgress.at(0)->GetVertices();
}