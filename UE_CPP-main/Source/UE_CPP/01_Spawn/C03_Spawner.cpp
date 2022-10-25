#include "01_Spawn/C03_Spawner.h"
#include "C02_Mesh.h"

AC03_Spawner::AC03_Spawner() {}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform;
	// FTransform : Location(위치), Rotation(회전), Scale (크기)
	//				를 저장할 수 있는 자료형입니다.
	
	// GetActorLocation() : 현재 액터의 위치를 가져옵니다.
	FVector location = GetActorLocation();
	// FVector : x , y , z 를 저장할 수 있는 자료형입니다.

	location.Y -= 200;

	for (UINT8 i = 0; i < 3; ++i)
	{
		// SetLocation() : 위치를 재설정합니다.
		transform.SetLocation(
			FVector(location.X, location.Y + (i * 200), location.Z));

		GetWorld()->SpawnActor<AC02_Mesh>(SpawnClass, transform);
		// GetWorld() : 액터가 배치되어 있는 월드를 가져옵니다.
		// SpawnActor<expression>(class, transform)
		// expression 형태의 클래스를 월드에 스폰 시켜주는 함수입니다.
	}



}


