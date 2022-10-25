#include "04_Particle/C01_Particle.h"
#include "Particles/ParticleSystemComponent.h"


AC01_Particle::AC01_Particle()
{
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	// ParticleSystemComponent 를 추가합니다.
	
	// 재생할 Particle 에셋을 로드합니다.
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	if (particle.Succeeded())
	{
		// ParticleSystemComponent 에 재생할 Particle을 설정합니다.
		Particle->SetTemplate(particle.Object);
		// Particle 이 자동으로 재생되지 않도록 설정합니다.
		Particle->bAutoActivate = false;
	}
}

void AC01_Particle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC01_Particle::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Particle->ResetParticles(); // Particle 을 리셋합니다.
	Particle->SetActive(true); // Particle 을 활성화합니다.

	FVector location = GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(EObjectTypeQuery::ObjectTypeQuery4); // 충돌할 유형을 추가합니다.

	TArray<AActor*> ignores; // 충돌 검사를 제외할 액터를 저장할 배열

	TArray<FHitResult> hitResult; // 충돌 검사가 이루어진 액터를 저장할 배열

	// SphereTraceMultiForObjects : 원형 충돌체를 일시적으로 생성합니다.
	//								충돌한 물체가 있다면 true 없다면 false 를 반환합니다.
	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects(
			 GetWorld(),	// SphereTrace 를 실행할 월드
			 location,   // 시작지점
			 location,   // 끝지점
			 300,        // 반지름
			 types,      // 충돌 검사 유형
			 false,
			 ignores,    // 충돌 검사 제외 목록
			 DrawDebugType, // SphereTrace 그리기 설정
			 hitResult,     // 충돌된 액터 목록
			 true);		   // 자기 자신 충돌 제외 여부 

	if (b) // 충돌한 물체가 존재한다면
	{
		// 충돌된 물체에 대하여 모두 반복합니다.
		for (const FHitResult& hit : hitResult)
		{
			// 충돌된 액터의 RootComponent 를 가져옵니다.
			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());

			// RootComponent 가 UStaticMeshComponent 이며 해당 객체가 물리 객체라면
			// IsSimulatingPhysics : 물리객체라면 ture 아니라면 false 를 반환합니다.
			if (mesh && mesh->IsSimulatingPhysics())
				mesh->AddRadialImpulse(
					location,	// 폭발할 위치
					1000,		// 폭발할 범위
					50000.0f,  // 폭발할 힘의 크기
					ERadialImpulseFalloff::RIF_MAX); // 폭발 기원으로부터의 강도 세기
			// AddRadialImpulse : 충격을 가하는 기능
		}
	}
}


