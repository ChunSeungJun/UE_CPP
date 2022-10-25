#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_LineTrace.generated.h"

UCLASS()
class UE_CPP_API AC01_LineTrace : public AActor
{
	GENERATED_BODY()
	
private :	
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* TextRender;

public:	
	AC01_LineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	void StartJump(class AActor* InActor);

private :
	TArray<class AC02_Cylinder*> Cylinders;
	TArray<AActor*> IgnoreActors;

};
