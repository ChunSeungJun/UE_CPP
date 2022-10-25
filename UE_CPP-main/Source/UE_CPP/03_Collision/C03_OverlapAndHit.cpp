#include "03_Collision/C03_OverlapAndHit.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC03_OverlapAndHit::AC03_OverlapAndHit()
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
	TextRender->Text = FText::FromString(FString("C03_Hit"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void AC03_OverlapAndHit::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentHit.AddDynamic(this, &AC03_OverlapAndHit::OnHit);

}

void AC03_OverlapAndHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString str;

	str.Append("Hit : " + OtherActor->GetName());
	str.Append(" / ");
	str.Append(FString::FromInt(++HitCount));

	TextRender->SetText(str);
}


