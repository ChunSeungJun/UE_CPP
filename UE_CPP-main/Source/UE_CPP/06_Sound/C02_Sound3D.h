#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Sound3D.generated.h"

UCLASS()
class UE_CPP_API AC02_Sound3D : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditAnywhere)
		class USoundAttenuation* SoundAttenuation;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleDefaultsOnly)
		class USoundCue* Sound; 

private :
	bool bStop;

public:	
	AC02_Sound3D();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private :
	UFUNCTION()
		void Play();
};
