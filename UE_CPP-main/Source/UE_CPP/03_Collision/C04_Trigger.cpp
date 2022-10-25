#include "03_Collision/C04_Trigger.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"

AC04_Trigger::AC04_Trigger()
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
	TextRender->Text = FText::FromString(FString("C04_Trigger"));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	
	if (mesh.Succeeded())
	{
		for (int32 i = 0; i < 3; i++)
		{
			FString str;
			str.Append("Meshes");
			str.Append(FString::FromInt(i + 1));
			Meshes[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(str));
			Meshes[i]->SetupAttachment(Root);
			// SetSimulatePhysics : 물리를 가동시킵니다.
			Meshes[i]->SetSimulatePhysics(true);
			Meshes[i]->SetRelativeLocation(FVector(250, i * 150, 250));
			Meshes[i]->SetStaticMesh(mesh.Object);
		}
	}

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpotLights");
		str.Append(FString::FromInt(i + 1));
		SpotLights[i] = CreateDefaultSubobject<USpotLightComponent>(FName(str));
		SpotLights[i]->SetupAttachment(Root);

		SpotLights[i]->SetRelativeLocation(FVector(250, i * 150, 250));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;   // 밝기를 10만으로 설정합니다.
		SpotLights[i]->OuterConeAngle = 25; // 원뿔의 각도를 25도로 설정합니다.
	}
}

void AC04_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC04_Trigger::OnBeginOverlap);

	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'"));

	for (int i = 0; i < 3; ++i)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(material, this);
		Meshes[i]->SetMaterial(0, Materials[i]);
		Meshes[i]->SetSimulatePhysics(false);

		// GetComponentToWorld : 월드에 존재하는 컴포넌트 좌표계를 가져옵니다.
		FTransform transform = Meshes[i]->GetComponentToWorld();
		WorldLocations[i] = transform.GetLocation();
	}
}

void AC04_Trigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	// IsBound() : 대리자에게 추가되어 있는 함수가 있는지 확인합니다.
	//             추가되어 있는 함수가 존재한다면 true 아니라면 false 를 반환합니다.
	if (OnMultiBeginOverlap.IsBound())
	{
		// OnMultiBeginOverlap 에 추가되어 있는 모든 함수를 실행합니다.
		OnMultiBeginOverlap.Broadcast(index, color);
	}

	OnPhysics(index, color);
	OnLight(index, color);
}

void AC04_Trigger::OnPhysics(int32 index, FLinearColor color)
{
	for (int i = 0; i < 3; i++)
	{
		Materials[i]->SetVectorParameterValue("Color", FLinearColor(1, 1, 1));

		Meshes[i]->SetSimulatePhysics(false);
		Meshes[i]->SetWorldLocation(WorldLocations[i]);
	}

	Materials[index]->SetVectorParameterValue("Color", color);

	Meshes[index]->SetSimulatePhysics(true);
}

void AC04_Trigger::OnLight(int32 index, FLinearColor color)
{
	for (int i = 0; i < 3; i++)
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));

	SpotLights[index]->SetLightColor(color);
}


