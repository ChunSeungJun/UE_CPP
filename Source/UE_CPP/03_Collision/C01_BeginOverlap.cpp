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

	// SetRelativeScale3D : 관계성(부모 자식관계에 속하는)이 있는 Transform 을 설정합니다. 
	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
	// bHiddenInGame : 인게임에서 가시성 여부를 결정할 수 있는 변수

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0));
	// FRotator : roll , pitch, yaw 값을 저장할 수 있는 자료형
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Black;
	// TextRenderColor : 텍스트 색상 결정 변수
	TextRender->Text = FText::FromString(FString("C01_BeginOverlap"));
	// Text : 텍스트 결정 변수
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	// HorizontalAlignment : 텍스트 정렬 결정 변수
}

void AC01_BeginOverlap::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AC01_BeginOverlap::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_BeginOverlap::OnEndOverlap);
	// OnActorBeginOverlap.AddDynamic(Object, Function)
	// 겹침이 시작했을 때 호출할 함수를 지정합니다.
	// Object : 등록할 함수를 가지고 있는 객체

}

void AC01_BeginOverlap::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str.Append("In : ");
	str.Append(OtherActor->GetName());
	// Append : str 뒤에 문자열을 잇습니다.
	// GetName : 월드아웃라이너의 이름을 가져옵니다.

	TextRender->SetText(FText::FromString(str));
	// TextRender 가 그리고 있는 텍스트를 변경합니다.
}

void AC01_BeginOverlap::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str.Append("Out : ");
	str.Append(OtherActor->GetName());

	TextRender->SetText(FText::FromString(str));
}

