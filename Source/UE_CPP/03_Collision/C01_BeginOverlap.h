#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_BeginOverlap.generated.h"

UCLASS()
class UE_CPP_API AC01_BeginOverlap : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	// BoxComponent : Box 형태의 기능
	//                Collision 기능에서 사용합니다.
	// Collision : 충돌체를 뜻하며 어떠한 액터가 충돌했는 지를 검사하는 기능
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	// SceneComponent : 보여주는 기능의 최상 부모입니다.
	// Root : SceneComponent 의 기준점
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;
	// TextRenderComponent : 텍스트를 그려주는 기능

public:	
	AC01_BeginOverlap();

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
		void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
