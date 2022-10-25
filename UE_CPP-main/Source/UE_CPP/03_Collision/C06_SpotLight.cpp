#include "03_Collision/C06_SpotLight.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "C04_Trigger.h"


AC06_SpotLight::AC06_SpotLight()
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
	TextRender->Text = FText::FromString(FString("C06_SpotLight"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpotLights");
		str.Append(FString::FromInt(i + 1));
		SpotLights[i] = CreateDefaultSubobject<USpotLightComponent>(FName(str));
		SpotLights[i]->SetupAttachment(Root);

		SpotLights[i]->SetRelativeLocation(FVector(250, i * 150, 250));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;   
		SpotLights[i]->OuterConeAngle = 25; 
	}
}

void AC06_SpotLight::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AC04_Trigger::StaticClass(), actors);

	AC04_Trigger* trigger = Cast<AC04_Trigger>(actors[0]);

	trigger->OnMultiBeginOverlap.AddUFunction(this, "OnLight");
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC06_SpotLight::OnBeginOverlap);
}

void AC06_SpotLight::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	OnLight(index, color);
}

void AC06_SpotLight::OnLight(int32 index, FLinearColor color)
{
	for (int i = 0; i < 3; i++)
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));

	SpotLights[index]->SetLightColor(color);
}


