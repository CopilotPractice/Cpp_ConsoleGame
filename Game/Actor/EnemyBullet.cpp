#include "EnemyBullet.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

EnemyBullet::EnemyBullet(const Vector2& position)
	: DrawableActor("vvv")
{
	//// ��ġ ����.
	this->position = position;

	yPosition = 2.0f;  //y������ 2 ����

	int ran = Random(1, 10); //Todo : ȭ�� �� ����

	ran = ran * 3;

	this->position.x = ran; // x������ ����
	//this->position = Vector2(xPosition, 2);
}

void EnemyBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);


	yPosition += speed * deltaTime;
	position.y = (int)yPosition;


	// ȭ�� ����� ����.
	if (yPosition >= Engine::Get().ScreenSize().y)
	{
		Destroy();
	}
	

	static float elapsedTime = 0.0f;
	static float fireInterval = RandomPercent(5.0f, 6.0f);

	elapsedTime += deltaTime;

	if (elapsedTime < fireInterval)
	{
		return;
	}


	elapsedTime = 0.0f;
	fireInterval = RandomPercent(5.0f, 6.0f);

	int ran = Random(1, 10); //Todo : ȭ�� �� ����

	ran = ran * 3;


	Engine::Get().AddActor(
		new EnemyBullet(Vector2(ran, 2))
	);
}