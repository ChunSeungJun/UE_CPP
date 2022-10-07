#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class UE_CPP_API AC03_Spawner : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> SpawnClass;
	// TSubclassOf<expression>
	// expression 형태를 상속받고 있는 모든 클래스 유형을
	// 담아줄수 있는 기능입니다.

public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

};
