#include "EnemyBullet.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

EnemyBullet::EnemyBullet(const Vector2& position)
	: DrawableActor("vvv")
{
	//// 위치 설정.
	this->position = position;

	yPosition = 2.0f;  //y포지션 2 고정

	int ran = Random(1, 10); //Todo : 화면 끝 설정

	ran = ran * 3;

	this->position.x = ran; // x포지션 랜덤
	//this->position = Vector2(xPosition, 2);
}

void EnemyBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);


	yPosition += speed * deltaTime;
	position.y = (int)yPosition;


	// 화면 벗어나면 제거.
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

	int ran = Random(1, 10); //Todo : 화면 끝 설정

	ran = ran * 3;


	Engine::Get().AddActor(
		new EnemyBullet(Vector2(ran, 2))
	);
}