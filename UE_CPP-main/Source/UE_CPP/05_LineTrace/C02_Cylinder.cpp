#include "05_LineTrace/C02_Cylinder.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

AC02_Cylinder::AC02_Cylinder()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cylinder.SM_Cylinder'");
	if (mesh.Succeeded())
	{
		Mesh->SetStaticMesh(mesh.Object);
		Mesh->SetRelativeScale3D(FVector(2, 2, 1));
	}
}

void AC02_Cylinder::BeginPlay()
{
	Super::BeginPlay();
	
}

