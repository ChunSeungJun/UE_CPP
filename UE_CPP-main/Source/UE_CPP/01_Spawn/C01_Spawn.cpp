#include "01_Spawn/C01_Spawn.h"

AC01_Spawn::AC01_Spawn()
{
	// Tick 함수 같은 경우 다른 함수와는 다르게
	// 매 프레임마다 호출되기 때문에 비용이 비쌉니다.
	// bCanEverTick 은 Tick 함수의 사용여부를 결정합니다.
	PrimaryActorTick.bCanEverTick = true;
}

void AC01_Spawn::BeginPlay()
{
	// Super : 상속받은 클래스의 함수를 실행시켜주는 기능입니다.
	Super::BeginPlay();
	
}

void AC01_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// DeltaTime : 게임이 시작한 후의 시간의 프레임

	// 프레임 : 초당 화면의 송출 주기 속도
}