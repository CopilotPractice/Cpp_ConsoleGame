#pragma once

#include <Actor/DrawableActor.h>
#include <Math/Vector2.h>

// 적 탄약 클래스.
class EnemyBullet : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyBullet, DrawableActor)

public:
	EnemyBullet(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:
	// 이동 관련 변수(속성).
	float speed = 15.0f;
	float yPosition = 0.0f;

	float xPosition = 0.0;
};
