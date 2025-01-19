#pragma once

#include <Actor/DrawableActor.h>

class GameLevel;
class P : public DrawableActor 
{
	RTTI_DECLARATIONS(P, DrawableActor)
public:
	P(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime)override;

private:
	GameLevel* refLevel = nullptr;
};