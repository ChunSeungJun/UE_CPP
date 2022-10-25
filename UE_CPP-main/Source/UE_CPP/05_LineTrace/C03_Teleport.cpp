#include "05_LineTrace/C03_Teleport.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "../Player/CPlayer.h"

AC03_Teleport::AC03_Teleport()
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
	TextRender->Text = FText::FromString(FString("C03_Teleport"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void AC03_Teleport::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AC03_Teleport::OnBeginOverlap);
}

void AC03_Teleport::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player) player->SetActorLocation(TeleportLocation);
}


