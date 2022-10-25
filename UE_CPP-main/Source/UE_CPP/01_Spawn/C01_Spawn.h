#pragma once

#include "CoreMinimal.h"
// CoreMinimal : Engine 에서 사용할 수 있는 기본 기능들을 모아놓은 파일
#include "GameFramework/Actor.h"
// Actor : 월드에 배치될 수 있는 기능을 모아놓은 파일
#include "C01_Spawn.generated.h"
// generated : 리플리케이트로 에디터에서 해당 파일 있다는 것을 알려주는 파일

/*
class template : cpp 와 h 가 같은 이름으로 선언됨

.h : 구성요소의 성분을 작성 , 성분들로 할 수 있는 행동의 이름 작성
Header File : 미리 만들어진 기능들을 모아놓은 파일로 #include 로 추가하게
              된다면 해당 파일에서 기능들을 사용할 수 있습니다.

.cpp : 행동들의 구체적인 기능을 작성
*/

// UCLASS() : Unreal 이 사용할 수 있는 class 라는 것을 명시
UCLASS()
class UE_CPP_API AC01_Spawn : public AActor
{
	GENERATED_BODY()
	// GENERATED_BODY()
	// 해당 위치부터 class 의 몸체라는 것을 명시합니다.
	
private :
	/*
	UPROPERTY() : Reflection 기능을 사용할 수 있는 키워드입니다.
				  UPROPERTY 가 명시되지 않은 변수들은 에디터에서 관리하지 않습니다.
	
	Unreal 에서는 세가지 타입이 존재합니다.
	1. C++ 타입 : C++ 로 이루어진 코드를 뜻합니다.
	2. 아키 타입 : C++ 코드를 베이스로 만들어진 블루프린트를 뜻합니다.
	3. 인스턴스 타입 : 아키 타입으로 월드에 배치되어 있는 복사본을 뜻합니다.
	
	EditAnywhere : 아키타입 , 인스턴스타입에서 모두 공개하며 편집이 가능합니다.
	EditInstanceOnly : 인스턴스타입에서만 공개하며 편집이 가능합니다.
	EditDefaultsOnly : 아키타입에서만 공개하며 편집이 가능합니다.
	VisibleAnywhere : 아키타입 , 인스턴스타입에서 모두 공개하며 편집이 불가능합니다.
	*/

	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	UPROPERTY(EditDefaultsOnly)
		int C = 30;
	UPROPERTY(VisibleAnywhere)
		int D = 40;

	int E = 50;

public:	
	AC01_Spawn();
	/* 
	생성자(Constructor) : 객체가 생성될 때 딱 한번 호출하는 함수입니다.
						  클래스명과 같은 이름의 함수입니다.

	객체(Object) : 어떠한 구조로 이루어진 소프트웨어에서 실체하는 메모리
	*/
protected:
	// BeginPlay() : 게임이 시작될 때 단 한번 호출하는 함수입니다.
	virtual void BeginPlay() override;

public:	
	// Tick() : 게임 시작 후 매 프레임마다 호출하는 함수입니다.
	virtual void Tick(float DeltaTime) override;
};
