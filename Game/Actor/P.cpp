#include "P.h"
#include <Engine/Engine.h>
#include <Level/GameLevel.h>

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
	// �����¿�.
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		 //�̵� �������� Ȯ��.
		if (refLevel->CanPlayerMove(Vector2(position.x - 4, position.y)))
		{
			refLevel->UpdateMap();
			position.x -= 3;	
		}

		/*position.x -= 1;
		position.x = position.x < 0 ? 0 : position.x;*/
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� �������� Ȯ��.
		if (refLevel->CanPlayerMove(Vector2(position.x + 2, position.y)))
		{	
			
			refLevel->UpdateMap();
			position.x += 3;
			/*position.x += 3;
			position.y -= 1;*/
			
		}
	}
}
