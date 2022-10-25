#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_SpotLight.generated.h"

UCLASS()
class UE_CPP_API AC06_SpotLight : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];

public:	
	AC06_SpotLight();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

private:
	UFUNCTION()
		void OnLight(int32 index, FLinearColor color);
};
