#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_AnimNotifyState.generated.h"

UCLASS()
class UE_CPP_API UC_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditAnywhere)
		bool bUnqequip; // 장착중인지 해제중인지에 대한 여부

private :
	// Editor 에서 보일 NotifyName 을 설정합니다.
	FString GetNotifyName_Implementation() const override; 

	// Notify 가 시작 될 때 기능을 추가합니다.
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim, float TotalDuration) override;

	// Notify 가 끝날 때 기능을 추가합니다.
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim) override;
};
