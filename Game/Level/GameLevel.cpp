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
	// 커서 감추기.
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
		// 랜덤으로 이동할 방향    선택.
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

    // 메시지 출력.

	//// 게임이 클리어됐으면, 게임 종료 처리.
	//if (isGameClear)
	//{
	//	// 대략 한 프레임 정도의 시간 대기.
	//	static float elapsedTime = 0.0f;
	//	elapsedTime += deltaTime;
	//	if (elapsedTime < 0.1f)
	//	{
	//		return;
	//	}

	//	// 커서 이동.
	//	Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

	//	// 메시지 출력.
	//	Log("Game Clear!");

	//	// 쓰레드 정지.
	//	Sleep(2000);

	//	// 게임 종료 처리.
	//	Engine::Get().QuitGame();
	//}
	
}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	// 탄약 및 적 캐릭터 배열 선언.
	List<EnemyBullet*> bullets;
	/*P* player = nullptr;*/

	// 액터 목록을 순회하면서 탄약과 적 캐릭터를 찾아 배열에 추가.
	for (Actor* actor : actors)
	{
		// 플레이어가 설정되지 않았으면 플레이어로 형변환.
		if (!player)
		{
			player = actor->As<P>();
			continue;
		}

		// 적으로 형변환 성공하면 목록에 추가.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
		}
	}

	// 플레이어를 못찾았거나 적 탄약이 없으면 충돌 처리하지 않고 종료.
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	// 두 배열을 순회하면서 충돌 처리.
	for (EnemyBullet* bullet : bullets)
	{
		// 플레이어가 비활성화 상태이면 건너뛰기.
		if (!player->IsAcive())
		{
			continue;
		}

		// 적과 탄약이 충돌했는지 확인.
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
	// 게임이 클리어된 경우 바로 종료.
	/*if (isGameClear)
	{
		return false;
	}*/


	// 이동하려는 위치에 계단이 있는지 확인.
	Stair* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 액터 찾기.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}


	// 검색한 액터가 이동 가능한 액터(계단)인지 확인.
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
////	//// 점수 확인을 위한 변수.
////	//int currentScore = 0;
////	//int targetScore = targets.Size();
////
////	//// 타겟 위치에 배치된 박스 개수 세기.
////	//for (auto* box : boxes)
////	//{
////	//	for (auto* target : targets)
////	//	{
////	//		// 점수 확인.
////	//		if (box->Position() == target->Position())
////	//		{
////	//			++currentScore;
////	//			break;
////	//		}
////	//	}
////	//}
////
////	//// 획득한 점수가 목표 점수와 같은지 비교.
////	//return currentScore == targetScore;
////}