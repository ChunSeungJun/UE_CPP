#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Bullet.generated.h"

UCLASS()
class UE_CPP_API AC_Bullet : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule; // 총알의 충돌체

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	// 투사체의 물리적 이동을 담당하는 기능입니다.

public:	
	AC_Bullet();

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpuluse,
			const FHitResult& Hit);

public :
	void Shoot(const FVector& InDirection);
};
