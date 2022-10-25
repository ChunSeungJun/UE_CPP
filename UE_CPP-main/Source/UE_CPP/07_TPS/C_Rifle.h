#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_Rifle.generated.h"

UCLASS()
class UE_CPP_API AC_Rifle : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket    = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrabMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* UnGrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* Curve; // 에임 전환 속도

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float AimDistance = 3000; // 투사체의 거리

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UMatineeCameraShake> CameraShake; // 샷 카메라 효과

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class USoundCue* MuzzleSoundCue; // 샷 사운드

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* FlashParticle; // 불빛 파티클

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* EjectParticle; // 연기 파티클

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class AC_Bullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* ImpactParticle; // 타격 파티클

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UMaterialInstanceConstant* ImpactDecal; // 총이 벽에 충돌할 경우 발생할 데칼

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private :
	class ACharacter* Owner; // 소유하고 있는 캐릭터

	bool bEquipped;   // 장착에 대한 여부
	bool bEquipping;  // 장착중에 대한 여부
	bool bAiming;     // 에임 상태에 대한 여부
	bool bFiring;     // 샷 여부
	bool bAutoFiring; // 연사, 단발 여부

	FTimeline Timeline;
	FOnTimelineFloat OnTimelineFloat;

	float PitchAngle; // 에임 사용 각도

	FTimerHandle AutoFireHandle;

public:	
	AC_Rifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	static AC_Rifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public :
	UFUNCTION()
		void Zooming(float Output);

private :
	void Firing(); // 샷 기능

public :
	// 장착
	void       Equip();
	void Begin_Equip();
	void   End_Equip();

	// 장착해제
	void   UnEquip();
	void Begin_UnEquip();
	void   End_UnEquip();

	// 에임
	void Begin_Aim();
	void   End_Aim();

	// 샷
	void Begin_Fire();
	void   End_Fire();

	// 연사 , 단발
	void ToggleAutoFire();

private :
	bool IsAvalibaleAim(); // 에임 가능 여부

public :
	FORCEINLINE bool GetEquipped() { return bEquipped;   }
	FORCEINLINE bool GetAiming()   { return bAiming;    }
	FORCEINLINE bool GetAutoFire() { return bAutoFiring; }
};
