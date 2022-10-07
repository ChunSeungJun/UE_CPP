#include "03_Collision/C05_Box.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"

AC05_Box::AC05_Box()
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
	TextRender->Text = FText::FromString(FString("C05_Box"));
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
}

void AC05_Box::BeginPlay()
{
	Super::BeginPlay();
	

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC05_Box::OnBeginOverlap);

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

void AC05_Box::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	OnPhysics(index, color);
	
}

void AC05_Box::OnPhysics(int32 index, FLinearColor color)
{
	for (int i = 0; i < 3; i++)
	{
		Materials[index]->SetVectorParameterValue("color", FLinearColor(1, 1, 1));

		Meshes[i]->SetSimulatePhysics(false);
		Meshes[i]->SetWorldLocation(WorldLocations[i]);
	}
	Materials[index]->SetVectorParameterValue("color", color);
	Meshes[index]->SetSimulatePhysics(true);
}



