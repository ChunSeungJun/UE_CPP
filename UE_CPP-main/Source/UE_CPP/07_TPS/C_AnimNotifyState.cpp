#include "07_TPS/C_AnimNotifyState.h"
#include "IRifle.h"

FString UC_AnimNotifyState::GetNotifyName_Implementation() const
{ return "Equip"; }

void UC_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Anim, TotalDuration);
    // Notify 의 실행주체에 Mesh 가 없다면 함수를 종료합니다.
    if (!MeshComp) return;  

    // Mesh 를 가지고 있는 주체가 IIRifle 을 소유하고 있는지 확인합니다.
    IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
    // IIRifle 을 가지고 있지 않다면 함수를 종료합니다.
    if (!rifle) return;

    // 장착 해제 상태라면
    if (bUnqequip)
    {
        // 라이플 장착 해제 시작을 실행하고 종료합니다.
        rifle->Begin_UnEquip_Rifle();
        return;
    }

    // 아니라면 라이플 장착 시작을 실행합니다.
    rifle->Begin_Equip_Rifle();
}

void UC_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim)
{
    Super::NotifyEnd(MeshComp, Anim);
    if (!MeshComp) return;

    IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
    if (!rifle) return;

    if (bUnqequip)
    {
        rifle->End_UnEquip_Rifle();
        return;
    }

    rifle->End_Equip_Rifle();
}
