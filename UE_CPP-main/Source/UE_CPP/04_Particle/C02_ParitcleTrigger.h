#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_ParitcleTrigger.generated.h"

UCLASS()
class UE_CPP_API AC02_ParitcleTrigger : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

public:	
	AC02_ParitcleTrigger();

protected:
	virtual void BeginPlay() override;
};
