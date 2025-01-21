#include "GameLevel.h"
#include "Engine/Engine.h"
#include <vector>
#include <Actor/Stair.h>
#include <Actor/P.h>
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
	for (int i = 0; i < 25;++i)
	{
		Wall* wallLeft = new Wall(Vector2(startMapX, i));
		actors.PushBack(wallLeft);
		Wall* wallRight = new Wall(Vector2(endMapX+4, i));
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
	for (int i = 0; i < 5; ++i) {
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
void GameLevel::SpawnBullet(float deltaTime)
{
	/*if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}*/

	// �� ����.
	static float elapsedTime = 0.0f;
	static float spawnTime = RandomPercent(3.0f, 4.0f);

	// Ÿ�̸�.
	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime)
	{
		return;
	}

	// Ÿ�̸� ����.
	elapsedTime = 0.0f;
	spawnTime = RandomPercent(3.0f, 4.0f);

	// �� ����.
	int index = Random(0, 20);

	EnemyBullet* enemybullet = new EnemyBullet(Vector2(index, 2));
	actors.PushBack(enemybullet);
}


void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	GameLevel::ProcessCollisionPlayerAndEnemyBullet();
	GameLevel::SpawnBullet(deltaTime);
	//if (isPlayerDead) {
	//	

	//	static float elapsedTime = 0.0f;
	//	elapsedTime += deltaTime;
	//	if (elapsedTime < 0.1f)
	//	{
	//		return;
	//	}
	//	//	// ������ ����.
	//	Sleep(2000);

	//	// ���� ���� ó��.
	//	// �޽��� ���.
	//	//system("cls");

	//	Log("Game Over!");
	//	
	//	// �޽��� ���.
	//	Engine::Get().QuitGame();
	//}


	// ������ Ŭ���������, ���� ���� ó��.
	//if (isGameOver)
	//{
	//	// �뷫 �� ������ ������ �ð� ���.
	//	static float elapsedTime = 0.0f;
	//	elapsedTime += deltaTime;
	//	if (elapsedTime < 0.1f)
	//	{
	//		return;
	//	}
	//	Sleep(2000);
	//	isPlayerDead = true;
	//	player->Destroy();
	//	// ������ ����.
	//	// Ŀ�� �̵�.
	//	char buffer1[256];
	//	snprintf(buffer1, 256, "Game Over");
	//	Engine::Get().Draw(Vector2(20, 20), buffer1);

	//	

	//	// ���� ���� ó��.
	//	Engine::Get().QuitGame();
	//}
	
}


void GameLevel::Draw()
{
	Super::Draw();

	char buffer[256];
	++time_timer;
	if (time_timer % 60 == 0) 
	{
		--time;
	}
	snprintf(buffer, 256, "Score: %d      �ð� ��: %d", score, time);
	Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), buffer);



	if (time == 0 || isGameOver)
	{
		snprintf(buffer, 256, "Game Over");
		Engine::Get().Draw(Vector2(13, 13), buffer);
		Engine::Get().QuitGame();
	}
	
}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	// ź�� �� �� ĳ���� �迭 ����.
	List<EnemyBullet*> bullets;
	//P* player = nullptr;

	// ���� ����� ��ȸ�ϸ鼭 ź��� �� ĳ���͸� ã�� �迭�� �߰�.
	for (Actor* actor : actors)
	{

		// ������ ����ȯ �����ϸ� ��Ͽ� �߰�.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
		}
	}

	// �÷��̾ ��ã�Ұų� �� ź���� ������ �浹 ó������ �ʰ� ����.
	/*if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}*/

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
			isGameOver = true;
		}
	}
}

void GameLevel::CheckGameOver()
{
	if (searchedActor == nullptr) {
		isGameOver = true;
	}
}


bool GameLevel::CanPlayerMove(const Vector2& position)
{

	// �̵��Ϸ��� ��ġ�� ����� �ִ��� Ȯ��.
	searchedActor = nullptr;

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

	isGameOver = true;
	return false;
}

void GameLevel::UpdateMap()
{
	if (currentStair == 1) 
	{
		for (auto* actor : map)
		{
			if(actor->GetFloor() == 1)
			{
				stairFirst.x = actor->Position().x;
				stairFirst.y = actor->Position().y;
			}
			if (actor->GetFloor() == 2) {
				stairSecond.x = actor->Position().x;
				stairSecond.y = actor->Position().y;
			}
			if (stairFirst.x != 0 && stairSecond.x != 0) {
				if (stairFirst.x - stairSecond.x > 0) {
					player->SetPosition(Vector2(stairFirst.x+1, stairFirst.y - 2));
				}
				else {
					player->SetPosition(Vector2(stairFirst.x + 1, stairFirst.y - 2));
				}
			}
			
		}
		++currentStair;
	}
	else if (currentStair == 2)
	{
		for (auto* actor : map)
		{
			if (stairSecond.x != 0 && stairSecond.x != 0) {
				if (stairSecond.x - stairSecond.x > 0) {
					player->SetPosition(Vector2(stairSecond.x + 1, stairSecond.y - 2));
				}
				else {
					player->SetPosition(Vector2(stairSecond.x + 1, stairSecond.y - 2));
				}
			}
		}
		++currentStair;
	}
	else 
	{
		for (auto* actor : map)
		{
			if (actor->GetFloor() == 6) {
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
				actor->SetFloor(6);
			}
		}
	}
	score += 100;
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