#pragma once
#include <Actor/DrawableActor.h>


class GameLevel;
class LimitTimer : public DrawableActor
{
	RTTI_DECLARATIONS(LimitTimer, DrawableActor)

public:
	LimitTimer(const char* number);

	virtual void Update(float deltaTime)override;

private:
	//float time;
	float StartTime = 30.0f;
	//GameLevel* refLevel = nullptr;
};