#include "P.h"
#include <Engine/Engine.h>
#include <Level/GameLevel.h>


class Stair;
P::P(const Vector2& position, GameLevel* level)
	:DrawableActor("P"), refLevel(level)
{
	this->position = position;

}

void P::Update(float deltaTime)
{
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
	// 상하좌우.
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		 //이동 가능한지 확인.
		if (refLevel->CanPlayerMove(Vector2(position.x - 4, position.y)))
		{
			refLevel->CheckGameOver();
			refLevel->UpdateMap();
			position.x -= 3;	
			//refLevel->CheckGameOver();
		}
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동 가능한지 확인.
		if (refLevel->CanPlayerMove(Vector2(position.x + 2, position.y)))
		{
			refLevel->CheckGameOver();
			refLevel->UpdateMap();
			position.x += 3;

			
			/*position.x += 3;
			position.y -= 1;*/

		}
	}
}
