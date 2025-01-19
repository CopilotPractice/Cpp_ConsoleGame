 #pragma once

#include <Actor/DrawableActor.h>

class GameLevel;
class Stair : public DrawableActor
{
	RTTI_DECLARATIONS(Stair, DrawableActor)
public:
	Stair(const Vector2& position, int floor);

	inline void SetFloor(int newFloor) { floor = newFloor; }

	inline int GetFloor() { return this->floor; }

private:
	int floor = 0;
};