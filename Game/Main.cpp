#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

int main()
{
	// 메모리 누수 확인.
	CheckMemoryLeak(); 

	Engine engine;
	engine.LoadLevel(new GameLevel());
	engine.Run();
}