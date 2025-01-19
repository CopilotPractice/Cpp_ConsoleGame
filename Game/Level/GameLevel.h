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


	// ������Ʈ �Լ�.
	virtual void Update(float deltaTime) override;

	// �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�.
	bool CanPlayerMove(const Vector2& position);

	void UpdateMap();


private:
	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�.
	/*bool CheckGameClear();*/

private:
	// ��� ����
	List<Stair*> map;

	int startMapX = 10;

	int endMapX = 30;

	//// �÷��̾� ����.
	P* player = nullptr;

	int Floor = 0;

	// ���� Ŭ���� ����.
	bool isGameClear = false;
};