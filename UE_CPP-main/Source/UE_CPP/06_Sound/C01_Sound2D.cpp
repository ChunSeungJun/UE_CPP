#include "06_Sound/C01_Sound2D.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/CPlayer.h"

AC01_Sound2D::AC01_Sound2D()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	TextRender->Text = FText::FromString(FString("C01_Sound2D"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	ConstructorHelpers::FObjectFinder<USoundCue> sound(L"SoundCue'/Game/Sounds/S_BGM_Cue.S_BGM_Cue'");
	if (sound.Succeeded()) Sound = sound.Object;
}

void AC01_Sound2D::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AC01_Sound2D::OnBeginOverlap);
}

void AC01_Sound2D::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<ACPlayer>(OtherActor)) return;

	if (!Audio)
	{
		// 오디오를 스폰합니다.
		Audio = UGameplayStatics::SpawnSound2D(GetWorld(), Sound);
		Audio->Play(); // 오디오를 재생합니다.
	}

	if (Audio)
	{
		// 오디오가 일시정지 상태였다면 해제하고
		// 아니라면 일시정지로 설정합니다.
		if (Audio->bIsPaused) Audio->SetPaused(false);
		else                  Audio->SetPaused(true);
	}
}

