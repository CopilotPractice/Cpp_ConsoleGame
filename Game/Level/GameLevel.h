#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>
#include <Actor/P.h>

// 소코반 게임 레벨.
class Stair;
class DrawableActor;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	void DrawMap();


	// 업데이트 함수.
	virtual void Update(float deltaTime) override;

	// 플레이어가 이동이 가능한 지 확인하는 함수.
	bool CanPlayerMove(const Vector2& position);

	void UpdateMap();

	void ProcessCollisionPlayerAndEnemyBullet();


private:
	// 박스를 옮긴 뒤 게임을 클리어했는지 확인하는 함수.
	/*bool CheckGameClear();*/

private:
	// 계단 액터
	List<Stair*> map;

	Vector2 fifthFloorPostion = Vector2(0, 0);


	int startMapX = 1;

	int endMapX = 22;

	//// 플레이어 액터.
	P* player = nullptr;

	int Floor = 0;

	// 게임 클리어 변수.
	bool isGameClear = false;

	bool isPlayerDead = false;

	Vector2 playerDeadPosition;
};