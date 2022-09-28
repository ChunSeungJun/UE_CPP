#include "01_Spawn/C03_Spawner.h"
#include "C02_Mesh.h"

AC03_Spawner::AC03_Spawner()
{
	

}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform;
	// FTransform : Location(��ġ), Rotation(ȸ��), Scale(ũ��)
	//				�� ������ �� �ִ� �ڷ����Դϴ�.
	
	// GetActorLocation() : ���� ������ ��ġ�� �����ɴϴ�.
	FVector location = GetActorLocation();
	// FVector : x , y , z �� ������ �� �ִ� �ڷ����Դϴ�.
	
	// SetLocation() : ��ġ�� �缳���մϴ�.
	
	for (UINT i = 0; i < 3; ++i) {
		transform.SetLocation(FVector(location.X , location.Y +(i * 200), location.Z));


		GetWorld()->SpawnActor<AC02_Mesh>(SpawnClass, transform);

	}
	
	
	// GetWorld() : ���Ͱ� ��ġ�Ǿ� �ִ� ���带 �����ɴϴ�.
	// SpawnActor<expression>(class, transform)
	// expression ������ Ŭ������ ���忡 ���� �����ִ� �Լ��Դϴ�.

}



