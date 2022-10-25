#include "Player/CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"

#include "Camera/CameraComponent.h"

#include "07_TPS/C_Rifle.h"
#include "07_TPS/C_UserWidget.h"



ACPlayer::ACPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	// Controller 의 yaw 값을 사용하지 않도록 설정합니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Actor 가 이동하는 방향 기준으로 회전하는 것을 설정합니다.
	GetCharacterMovement()->MaxWalkSpeed = 400;
	// 캐릭터의 이동속도를 400으로 설정합니다.

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	if (mesh.Succeeded()) GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// FClassFinder : Class , Blueprint 형식의 에셋을 찾습니다.
	// Object 가 아닌 Class 로 설정합니다.
	// 우리가 추가할 에셋은 애니메이션이 아닌 애니메이션 블루프린트이기
	// 때문에 FClassFinder 형식으로 찾아야합니다.
	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	if (anim.Succeeded()) GetMesh()->SetAnimClass(anim.Class);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	// SpringArm 의 z 위치를 60 으로 설정합니다.
	SpringArm->TargetArmLength = 200;
	// SpringArm 의 길이를 200으로 설정합니다.
	SpringArm->bUsePawnControlRotation = true;
	// SpringArm 이 컨트롤러의 회전값을 사용하도록 합니다.
	SpringArm->SocketOffset = FVector(0, 60, 0);
	// SpringArm 의 시작 지점의 y 위치를 60 으로 설정합니다.

	ConstructorHelpers::FClassFinder<UC_UserWidget> autoFire(L"WidgetBlueprint'/Game/Blueprints/07_TPS/BP_UserWidget.BP_UserWidget_C'");
	if (autoFire.Succeeded()) AutoFireClass = autoFire.Class;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// 해당 캐릭터가 플레이어라는 것을 설정합니다.
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	Rifle = AC_Rifle::Spawn(GetWorld(), this);
	AutoFire = CreateWidget<UC_UserWidget, APlayerController>(GetController<APlayerController>(), AutoFireClass);
	AutoFire->AddToViewport();
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",    this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",      this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook",   this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom",           this, &ACPlayer::OnZoom);


	PlayerInputComponent->BindAction("Run",      EInputEvent::IE_Pressed,  this, &ACPlayer::Run);
	PlayerInputComponent->BindAction("Run",      EInputEvent::IE_Released, this, &ACPlayer::Walk);
	PlayerInputComponent->BindAction("Rifle",    EInputEvent::IE_Pressed,  this, &ACPlayer::OnRifle_Equip);
	PlayerInputComponent->BindAction("Aim",      EInputEvent::IE_Pressed,  this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim",      EInputEvent::IE_Released, this, &ACPlayer::OffAim);
	PlayerInputComponent->BindAction("Fire",     EInputEvent::IE_Pressed,  this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire",     EInputEvent::IE_Released, this, &ACPlayer::OffFire);
	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed,  this, &ACPlayer::OnAutoFire);


}

void ACPlayer::OnMoveForward(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	// Controller 의 yaw 회전값을 저장합니다.
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal();
	// Controller 기준의 앞 방향을 1로 정규화된 값으로 저장합니다.

	AddMovementInput(direction, axis);
	// 캐릭터를 방향으로 이동시킵니다.
}

void ACPlayer::OnMoveRight(float axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal();
	// Controller 기준의 오른쪽 방향을 1로 정규화된 값으로 저장합니다.

	AddMovementInput(direction, axis);
}

void ACPlayer::OnHorizontalLook(float axis)
{ AddControllerYawInput(axis); }

void ACPlayer::OnVerticalLook(float axis)
{ AddControllerPitchInput(axis); }

void ACPlayer::OnZoom(float axis)
{
	SpringArm->TargetArmLength += (ZoomSpeed * axis * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, ZoomRange.X, ZoomRange.Y);
	
}

void ACPlayer::Run()
{
	// 캐릭터 이동속도를 600으로 설정
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::Walk()
{
	// 캐릭터 이동속도를 400으로 설정
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::OnRifle_Equip()
{ Rifle->Equip(); }

void ACPlayer::OnAim()
{ Rifle->Begin_Aim(); }

void ACPlayer::OffAim()
{ Rifle->End_Aim(); }

void ACPlayer::OnFire()
{ Rifle->Begin_Fire(); }

void ACPlayer::OffFire()
{ Rifle->End_Fire(); }

void ACPlayer::OnAutoFire()
{
	Rifle->ToggleAutoFire();
	Rifle->GetAutoFire() ? AutoFire->On() : AutoFire->Off();
}

void ACPlayer::Begin_Equip_Rifle()
{ Rifle->Begin_Equip(); }

void ACPlayer::End_Equip_Rifle()
{ Rifle->End_Equip(); }

void ACPlayer::Begin_UnEquip_Rifle()
{ Rifle->Begin_UnEquip(); }

void ACPlayer::End_UnEquip_Rifle()
{ Rifle->End_UnEquip(); }

bool ACPlayer::Get_Equip_Rifle()
{ return Rifle->GetEquipped(); }

bool ACPlayer::Get_Aim_Rifle()
{ return Rifle->GetAiming(); }


