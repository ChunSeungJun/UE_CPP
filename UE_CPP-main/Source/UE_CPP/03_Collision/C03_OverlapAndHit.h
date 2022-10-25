#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_OverlapAndHit.generated.h"

UCLASS()
class UE_CPP_API AC03_OverlapAndHit : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

private :
	int32 HitCount;

public:	
	AC03_OverlapAndHit();

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
				   AActor* OtherActor,
				   UPrimitiveComponent* OtherComp,
				   FVector NormalImpulse,
				   const FHitResult& Hit);

};
