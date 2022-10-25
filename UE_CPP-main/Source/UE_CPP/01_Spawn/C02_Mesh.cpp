#include "01_Spawn/C02_Mesh.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AC02_Mesh::AC02_Mesh()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
}

void AC02_Mesh::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, L"MaterialInstanceConstant'/Game/Mesh/M_BasicShape_Inst.M_BasicShape_Inst'");
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	Material = UMaterialInstanceDynamic::Create(material, this);

	Mesh->SetMaterial(0, Material);


	// 지역변수
	// 선언된 함수내에서만 사용가능한 변수
	// 
	// 맴버변수
	// 해당 클래스 안에서 선언된 변수로 클래스의 함수에서 모두 접근이 가능합니다.

	// Timer : 주기적으로 실행할 명령을 설정하는 기능
	// K2_SetTimer(타이머 소유주, 호출할 함수 이름, 실행할 주기, 반복실행여부);
	// 호출할 함수는 UFUNCTION  으로 지정된 함수여야 합니다.
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AC02_Mesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC02_Mesh::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	Material->SetVectorParameterValue("Color", color);
}


