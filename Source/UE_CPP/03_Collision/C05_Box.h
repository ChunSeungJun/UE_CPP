#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_Box.generated.h"

UCLASS()
class UE_CPP_API AC05_Box : public AActor
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
		class UStaticMeshComponent* Meshes[3];

public:	
	AC05_Box();

protected:
	virtual void BeginPlay() override;

public:	
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

private:
	// �ڽ����� ������ ��ȯ�ϰ� �����ϵ����ϴ� �Լ�
	void OnPhysics(int32 index, FLinearColor color);

private:
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocations[3]; // �ʱ⿡ �����Ǿ� �ִ� ���ڵ��� ��ġ�� ���� ����

};
