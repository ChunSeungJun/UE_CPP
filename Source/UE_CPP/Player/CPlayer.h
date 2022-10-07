#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_CPP_API ACPlayer : public ACharacter
{
	// ACharacter  
	// SkeltealMeshComponent : 뼈대 메쉬 기능
	// ArrowComponent : 방향 기능
	// CharacterMovementComponent : 움직임 기능
	// Pawn : 입력받을 수 있는 Actor
	// CapsuleComponent : Capsule 형태의 충돌체
	// 을 기본적으로 가지고 있는 클래스입니다.

	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	// Camera 가 사물을 감지하여 플레이어를 촬영할 수 
	// 있도록 SpringArmComponent 를 추가합니다.

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
	// Player 를 보여줄 수 있도록 Camera 를 추가합니다.

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

	
	
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	void OnMoveForward(float axis);	// 앞 뒤 이동
	void OnMoveRight(float axis);   // 좌 우 이동

	void OnHorizontalLook(float axis); 
	void OnVerticalLook(float axis);

	void Run();
	void Walk();

};
