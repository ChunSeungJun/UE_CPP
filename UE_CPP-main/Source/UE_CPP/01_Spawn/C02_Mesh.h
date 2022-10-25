#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Mesh.generated.h"

UCLASS()
class UE_CPP_API AC02_Mesh : public AActor
{
	GENERATED_BODY()
	
private :
	// Mesh : 형태
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	// UStaticMeshComponent 
	// 해당 클래스에서 Mesh 기능을 추가할 수 있습니다.

	class UMaterialInstanceDynamic* Material;

public:	
	AC02_Mesh();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION : 에디터에서 관리할 함수라는 것을 명시하는 키워드
	UFUNCTION()
	void ChangeColor();
};
