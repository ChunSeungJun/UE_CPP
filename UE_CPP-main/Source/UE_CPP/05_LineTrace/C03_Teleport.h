#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Teleport.generated.h"

UCLASS()
class UE_CPP_API AC03_Teleport : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

private:
	UPROPERTY(EditInstanceOnly)
		FVector TeleportLocation;

public:	
	AC03_Teleport();

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
