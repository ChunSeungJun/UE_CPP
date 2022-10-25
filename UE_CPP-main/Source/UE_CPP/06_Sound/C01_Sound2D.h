#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Sound2D.generated.h"

UCLASS()
class UE_CPP_API AC01_Sound2D : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleDefaultsOnly)
		class USoundCue* Sound; // USoundCue : 사운드입니다.

private :
	class UAudioComponent* Audio;
	// UAudioComponent : 사운드를 재생할 수 있는 기능입니다.

public:	
	AC01_Sound2D();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
