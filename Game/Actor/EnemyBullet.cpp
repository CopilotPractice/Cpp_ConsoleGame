#include "EnemyBullet.h"
#include "Engine/Engine.h"

EnemyBullet::EnemyBullet(const Vector2& position)
	: DrawableActor("*")
{
	//// ��ġ ����.
	this->position = position;

	yPosition = 2.0f;  //y������ 2 ����

	int xPosition = Random(1, Engine::Get().ScreenSize().y - 5); // x������ ����
	this->position = Vector2(xPosition, 2);
}

void EnemyBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);


	yPosition += speed * deltaTime;
	position.y = (int)yPosition;


	if (position.y > Engine::Get().ScreenSize().y)
	{
		Destroy();
	}

	static float elapsedTime = 0.0f;
	static float fireInterval = RandomPercent(1.0f, 2.0f);

	elapsedTime += deltaTime;

	if (elapsedTime < fireInterval)
	{
		return;
	}


	elapsedTime = 0.0f;
	fireInterval = RandomPercent(1.0f, 2.0f);

	int randomX = Random(1, Engine::Get().ScreenSize().y - 5);



	Engine::Get().AddActor(
		new EnemyBullet(Vector2(randomX, 2))
	);
}