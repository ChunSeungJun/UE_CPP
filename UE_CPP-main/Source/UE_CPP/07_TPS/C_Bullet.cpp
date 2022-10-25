#include "07_TPS/C_Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"


AC_Bullet::AC_Bullet()
{
	Capsule    = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh       = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	Capsule->SetRelativeRotation(FRotator(90, 0, 0)); 
	Capsule->SetCapsuleHalfHeight(50);
	Capsule->SetCapsuleRadius(2);
	Capsule->SetCollisionProfileName("BlockAllDynamic");
	// Overlap 이 아닌 물리적 즉 Hit 충돌을 감지하도록 설정합니다.

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> material(L"MaterialInstanceConstant'/Game/Materials/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);

	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeScale3D(FVector(1, 0.025f, 0.025f));
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));

	Projectile->InitialSpeed = 2e+4f; // 처음 투사체 속도
	Projectile->MaxSpeed = 2e+4f;     // 투사체 최고 속도
	Projectile->ProjectileGravityScale = 0; // 중력값
}

void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	// Capsule 이 물리적 충돌이 일어난다면 OnHit 함수를 실행합니다.
	Capsule->OnComponentHit.AddDynamic(this, &AC_Bullet::OnHit);
}

void AC_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	Destroy(); // 해당 객체를 파괴합니다.
}

void AC_Bullet::Shoot(const FVector& InDirection)
{
	// Velocity : 방향으로 날아가는 속력
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
	// 투사체의 Velocity 를 InDirection 의 방향으로 초기 속력 만큼 날아가도록 설정합니다.
}

