#include "LimitTimer.h"
#include "Engine/Engine.h";
#include <string>

LimitTimer::LimitTimer(const char* number)
	:DrawableActor(number)
{

	this->position = Vector2(Engine::Get().ScreenSize().x - 2, Engine::Get().ScreenSize().y - 10);
	color = Color::Green;

}


void LimitTimer::Update(float deltaTime)
{
	Super::Update(deltaTime);

	StartTime -= 1.0f;

	int time = StartTime;

	std::string time_char = std::to_string(time);

	LimitTimer* timer = new LimitTimer("30");
	actors.PushBack(timer);
	
	//Engine::Get().AddActor(new LimitTimer(time_char.data()));
}
