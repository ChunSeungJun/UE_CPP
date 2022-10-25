#include "06_Sound/C02_Sound3D.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Player/CPlayer.h"

AC02_Sound3D::AC02_Sound3D()
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
	TextRender->Text = FText::FromString(FString("C01_Sound3D"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	ConstructorHelpers::FObjectFinder<USoundCue> sound(L"SoundCue'/Game/Sounds/S_Stepdirt_Cue.S_Stepdirt_Cue'");
	if (sound.Succeeded()) Sound = sound.Object;
}

void AC02_Sound3D::BeginPlay()
{
	Super::BeginPlay();
	bStop = true;
	
	OnActorBeginOverlap.AddDynamic(this, &AC02_Sound3D::OnBeginOverlap);
}

void AC02_Sound3D::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!Cast<ACPlayer>(OtherActor)) return;

	if (bStop)
	{
		bStop = false;
		UKismetSystemLibrary::K2_SetTimer(this, "Play", 0.5f, true);
	}
	else
	{
		bStop = true;
		UKismetSystemLibrary::K2_ClearTimer(this, "Play");
	}
}

void AC02_Sound3D::Play()
{
	// 소리 감쇠가 존재한다면 특정 위치에서 사운드를 재생합니다.
	if (SoundAttenuation)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),
			Sound,
			GetActorLocation(),
			1, 1, 0,
			SoundAttenuation);
}

