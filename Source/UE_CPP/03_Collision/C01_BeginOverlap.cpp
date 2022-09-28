#include "03_Collision/C01_BeginOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_BeginOverlap::AC01_BeginOverlap()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);

}

void AC01_BeginOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}



