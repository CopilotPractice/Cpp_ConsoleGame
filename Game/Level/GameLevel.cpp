#include "GameLevel.h"
#include "Engine/Engine.h"
#include <vector>
#include <Actor/Stair.h>
#include <Actor/P.h>
#include <Actor/LimitTimer.h>
#include "Actor/EnemyBullet.h"
#include "Render/ScreenBuffer.h"
#include "Actor/Wall.h"


GameLevel::GameLevel()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);


    DrawMap();
	


}

void GameLevel::DrawMap()
{   
	for (int i = 0; i < Engine::Get().ScreenSize().y;++i)
	{
		Wall* wallLeft = new Wall(Vector2(0, i));
		actors.PushBack(wallLeft);
		Wall* wallRight = new Wall(Vector2(Engine::Get().ScreenSize().y, i));
		actors.PushBack(wallRight);
	}
	
	EnemyBullet* enemybullet = new EnemyBullet(Vector2(1, 10));
	actors.PushBack(enemybullet);

	/*LimitTimer* timer = new LimitTimer("30");
	actors.PushBack(timer);*/

    static Vector2 previousPosition = Vector2((startMapX + endMapX)/2, 20);
    Stair* stair = new Stair(Vector2(previousPosition.x, previousPosition.y), 1);
    actors.PushBack(stair);
    map.PushBack(stair);

	player = new P(Vector2(previousPosition.x+1, previousPosition.y-1), this);
	actors.PushBack(player);

	int newFloor = 2;
	for (int i = 0; i < 4; ++i) {
		// �������� �̵��� ����    ����.
		int random = Random(1, 10);

		if (previousPosition.x-3 < startMapX) 
		{
			random = 2;
		}
		else if (previousPosition.x > endMapX)
		{
			random = 1;
		}
		if (random % 2 == 0)
		{
			Stair* stair = new Stair(Vector2(previousPosition.x + 3, previousPosition.y - 1), newFloor);
			actors.PushBack(stair);
			map.PushBack(stair);
			previousPosition = Vector2(previousPosition.x + 3, previousPosition.y - 1);
		}
		else
		{
			Stair* stair = new Stair(Vector2(previousPosition.x - 3, previousPosition.y - 1), newFloor);
			actors.PushBack(stair);
			map.PushBack(stair);
			previousPosition = Vector2(previousPosition.x - 3, previousPosition.y - 1);
		}
		//++Floor;
		++newFloor;
	}
	
}



void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	GameLevel::ProcessCollisionPlayerAndEnemyBullet();

    // �޽��� ���.

	//// ������ Ŭ���������, ���� ���� ó��.
	//if (isGameClear)
	//{
	//	// �뷫 �� ������ ������ �ð� ���.
	//	static float elapsedTime = 0.0f;
	//	elapsedTime += deltaTime;
	//	if (elapsedTime < 0.1f)
	//	{
	//		return;
	//	}

	//	// Ŀ�� �̵�.
	//	Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

	//	// �޽��� ���.
	//	Log("Game Clear!");

	//	// ������ ����.
	//	Sleep(2000);

	//	// ���� ���� ó��.
	//	Engine::Get().QuitGame();
	//}
	
}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	// ź�� �� �� ĳ���� �迭 ����.
	List<EnemyBullet*> bullets;
	/*P* player = nullptr;*/

	// ���� ����� ��ȸ�ϸ鼭 ź��� �� ĳ���͸� ã�� �迭�� �߰�.
	for (Actor* actor : actors)
	{
		// �÷��̾ �������� �ʾ����� �÷��̾�� ����ȯ.
		if (!player)
		{
			player = actor->As<P>();
			continue;
		}

		// ������ ����ȯ �����ϸ� ��Ͽ� �߰�.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
		}
	}

	// �÷��̾ ��ã�Ұų� �� ź���� ������ �浹 ó������ �ʰ� ����.
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	// �� �迭�� ��ȸ�ϸ鼭 �浹 ó��.
	for (EnemyBullet* bullet : bullets)
	{
		// �÷��̾ ��Ȱ��ȭ �����̸� �ǳʶٱ�.
		if (!player->IsAcive())
		{
			continue;
		}

		// ���� ź���� �浹�ߴ��� Ȯ��.
		if (player->Intersect(*bullet))
		{
			isPlayerDead = true;
			playerDeadPosition = Vector2(player->Position().x, player->Position().y);
			player->Destroy();
		}
	}
}


bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����.
	/*if (isGameClear)
	{
		return false;
	}*/


	// �̵��Ϸ��� ��ġ�� ����� �ִ��� Ȯ��.
	Stair* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ��ġ�� ���� ã��.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}


	// �˻��� ���Ͱ� �̵� ������ ����(���)���� Ȯ��.
	if (searchedActor) {
		return true;
	}

	return false;
}

void GameLevel::UpdateMap()
{
	for (auto* actor : map)
	{
		/*if (!actor->IsAcive()) {
			continue;
		}*/
		if (actor->GetFloor() == 5) {
			fifthFloorPostion = actor->Position();
			break;
		}
		
	}
	for (auto* actor : map)
	{
		int actorX = actor->Position().x;
		int actorY = actor->Position().y;
		actor->SetPosition(Vector2(actorX, actorY + 1));
		actor->SetFloor(actor->GetFloor() - 1);

		if (actor->GetFloor() == 0) 
		{
			int random = Random(1, 10);
			if (fifthFloorPostion.x - 3 < startMapX)
			{
				random = 2;
			}
			else if (fifthFloorPostion.x + 3 > endMapX)
			{
				random = 1;
			}
			if (random % 2 == 0)
			{
				actor->SetPosition(Vector2(fifthFloorPostion.x + 3, fifthFloorPostion.y));
			}
			else
			{
				actor->SetPosition(Vector2(fifthFloorPostion.x - 3, fifthFloorPostion.y));
				
			}
			actor->SetFloor(5);
		}
	}
	/*int random = Random(1, 10);
	if (fifthFloorPostion.x - 3 < startMapX)
	{
		random = 2;
	}
	else if (fifthFloorPostion.x + 3 > endMapX)
	{
		random = 1;
	}
	if (random % 2 == 0)
	{
		Stair* stair = new Stair(Vector2(fifthFloorPostion.x + 3, fifthFloorPostion.y), 5);
		actors.PushBack(stair);
		map.PushBack(stair);
	}
	else
	{
		Stair* stair = new Stair(Vector2(fifthFloorPostion.x - 3, fifthFloorPostion.y), 5);
		actors.PushBack(stair);
		map.PushBack(stair);
	}*/
}

//
////bool GameLevel::CheckGameClear()
////{
////	//// ���� Ȯ���� ���� ����.
////	//int currentScore = 0;
////	//int targetScore = targets.Size();
////
////	//// Ÿ�� ��ġ�� ��ġ�� �ڽ� ���� ����.
////	//for (auto* box : boxes)
////	//{
////	//	for (auto* target : targets)
////	//	{
////	//		// ���� Ȯ��.
////	//		if (box->Position() == target->Position())
////	//		{
////	//			++currentScore;
////	//			break;
////	//		}
////	//	}
////	//}
////
////	//// ȹ���� ������ ��ǥ ������ ������ ��.
////	//return currentScore == targetScore;
////}