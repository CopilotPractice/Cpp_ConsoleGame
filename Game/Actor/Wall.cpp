#include "Wall.h"

Wall::Wall(const Vector2& position)
	: DrawableActor("||")
{

	this->position = position;

	color = Color::Blue;

}
