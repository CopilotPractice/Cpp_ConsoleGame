#include "Stair.h"

Stair::Stair(const Vector2& position, int floor)
	: DrawableActor("==="), floor(floor)
{

	this->position = position;

	color = Color::Red;

}
