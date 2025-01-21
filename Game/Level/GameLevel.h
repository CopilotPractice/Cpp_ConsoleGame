#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>
#include <Actor/P.h>

// ���ڹ� ���� ����.
class Stair;
class DrawableActor;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	void DrawMap();

	void SpawnBullet(float deltaTime);


	// ������Ʈ �Լ�.
	virtual void Update(float deltaTime) override;

	//void ToggleMenu();

	virtual void Draw() override;

	// �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�.
	bool CanPlayerMove(const Vector2& position);

	void UpdateMap();

	void ProcessCollisionPlayerAndEnemyBullet();

	void CheckGameOver();

private:
	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�.
	/*bool CheckGameClear();*/
	

private:
	// ��� ����
	List<Stair*> map;

	Vector2 fifthFloorPostion = Vector2(0, 0);

	bool showGameOver = true;

	int startMapX = 1;

	int endMapX = 30;

	//// �÷��̾� ����.
	P* player = nullptr;

	int Floor = 0;

	// ���� Ŭ���� ����.
	bool isGameOver = false;

	bool isPlayerDead = false;

	Vector2 playerDeadPosition;

	int currentStair = 1;

	Vector2 stairFirst = Vector2(0,0);
	Vector2 stairSecond = Vector2(0, 0);

	int time = 10;
	int time_timer = 0;
	int score = 0;

	Stair* searchedActor = nullptr;
};