#include "07_TPS/C_Rifle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Gameframework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Gameframework/PlayerController.h"
#include "Gameframework/SpringArmComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"

#include "Animation/AnimMontage.h"

#include "Camera/CameraComponent.h"

#include "Sound/SoundCue.h"

#include "Particles/ParticleSystemComponent.h"

#include "Materials/MaterialInstanceConstant.h"

#include "C_Bullet.h"
#include "CHUD.h"


AC_Rifle::AC_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Character/Animations/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> unGrabMontage(L"AnimMontage'/Game/Character/Animations/Rifle/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	if (unGrabMontage.Succeeded()) UnGrabMontage = unGrabMontage.Object;

	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(L"CurveFloat'/Game/Blueprints/07_TPS/Curve_Aim.Curve_Aim'");
	if (curve.Succeeded()) Curve = curve.Object;

	ConstructorHelpers::FObjectFinder<USoundCue> sound(L"SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	if (sound.Succeeded()) MuzzleSoundCue = sound.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> flash(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	if (flash.Succeeded()) FlashParticle = flash.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> eject(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	if (eject.Succeeded()) EjectParticle = eject.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> impact(L"ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	if (impact.Succeeded()) ImpactParticle = impact.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Materials/M_Decal_Inst.M_Decal_Inst'");
	if (decal.Succeeded()) ImpactDecal = decal.Object;

	ConstructorHelpers::FClassFinder<UMatineeCameraShake> cameraShake(L"Blueprint'/Game/Blueprints/07_TPS/BP_CameraShake.BP_CameraShake_C'");
	if (cameraShake.Succeeded()) CameraShake = cameraShake.Class;

	ConstructorHelpers::FClassFinder<AC_Bullet> bullet(L"Blueprint'/Game/Blueprints/07_TPS/BP_Bullet.BP_Bullet_C'");
	if (bullet.Succeeded()) BulletClass = bullet.Class;
}

void AC_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
	// ???????? ??????????.
	Owner = Cast<ACharacter>(GetOwner());
	// ???????? ?????? HolsterSocket ?? ???? ?????? 
	// ???? ?????????? ?????? ?? ??????????.
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

	OnTimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimelineFloat);
	Timeline.SetPlayRate(200);
}

void AC_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);

	if (!bAiming) return;

	UCameraComponent* camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));

	// ???????? ?? ?????? ??????????.
	FVector direction = camera->GetForwardVector();
	// ???????? ???? ?????????? ??????????.
	FTransform transform = camera->GetComponentToWorld();
	// ???????? ???? ?????? ???????? ??????????.
	FVector start = transform.GetLocation() + direction;
	// start ?? ???????? AimDistance ?????? ?? ???????? ??????????.
	FVector end = transform.GetLocation() + direction * AimDistance;

	ACHUD* hud = Owner->GetController<APlayerController>()->GetHUD<ACHUD>();

	// ???? ?????????? ?????? ?????? Player ?? ???????? ?????? ??????????.
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(Owner);

	// ?????? ?????? ?????? hitResult ?? ??????????.
	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery3,
		false, ignoreActors, EDrawDebugTrace::None, hitResult, true);

	// bBlockingHit : ?????????? ?????????? ????????
	//                ???? ?????? ???????????? ???? ????  
	if (hitResult.bBlockingHit) hud->EnableTarget();
	else                        hud->DisableTarget();
}

AC_Rifle* AC_Rifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params; // ???? ?????? ???? ???????? ??????????.
	params.Owner = InOwner; // ?????????? ?????? InOwner ?? ???????? ??????????.

	// ?????????? ?????? InWorld ?? AC_Rifle ?? ???????? ???????? ??????????.
	return InWorld->SpawnActor<AC_Rifle>(params);
}

void AC_Rifle::Zooming(float Output)
{
	UCameraComponent* camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	camera->FieldOfView = Output;
}

void AC_Rifle::Firing()
{
	FVector direction, start, end;

	// ?????? ??????
	if (IsAvalibaleAim())
	{
		UCameraComponent* camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));

		direction = camera->GetForwardVector();
		FTransform transform = camera->GetComponentToWorld();
		start = transform.GetLocation() + direction;
		end   = transform.GetLocation() + direction * AimDistance;

		direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(direction, 0.2f);

		APlayerController* controller = Owner->GetController<APlayerController>();

		if (CameraShake) controller->PlayerCameraManager->StartCameraShake(CameraShake);
	}
	// ??????
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	{
		if (MuzzleSoundCue)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MuzzleSoundCue, muzzleLocation);
	}
	// ??????
	{
		if (FlashParticle)
			UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
		if (EjectParticle)
			UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	}
	// ????????
	if (BulletClass)
	{
		FVector spawnLocation = muzzleLocation + direction * 100;
		AC_Bullet* bullet = GetWorld()->SpawnActor<AC_Bullet>(
			BulletClass, spawnLocation, direction.Rotation());
		bullet->Shoot(direction);
	}
	// ???????? 

	PitchAngle -= 0.25 * GetWorld()->DeltaTimeSeconds;
	Owner->AddControllerPitchInput(PitchAngle);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(Owner);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1,
		false, ignoreActors, EDrawDebugTrace::None, hitResult, true);

	if (hitResult.bBlockingHit)
	{
		FRotator rotator = hitResult.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation
		(GetWorld(), ImpactParticle, hitResult.Location, rotator);

		UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(), ImpactDecal, FVector(5), hitResult.Location, rotator, 10);
		decal->SetFadeScreenSize(0);

		UStaticMeshComponent* mesh = 
			Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());

		if (mesh && mesh->BodyInstance.bSimulatePhysics)
		{
			direction = hitResult.GetActor()->GetActorLocation() -
				Owner->GetActorLocation();

			direction.Normalize();

			mesh->AddImpulseAtLocation(
				direction * 300 * mesh->GetMass(), Owner->GetActorLocation());
		}

	}
}

void AC_Rifle::Equip()
{
	// ???????? ???? ?????????? ?????? ??????????.
	if (bEquipping) return;

	// ???????? ???? ?????????? ??????????.
	bEquipping = true;
	
	// ???????? ??????????
	if (bEquipped == true)
	{
		// ???? ?????? ??????????.
		UnEquip();
		return;
	}

	// GrabMontage ?? 2?? ?????? ??????????.
	Owner->PlayAnimMontage(GrabMontage, 2);
}

void AC_Rifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(Owner->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket);
}

void AC_Rifle::End_Equip()
{ bEquipping = false; }

void AC_Rifle::UnEquip()
{
	Owner->PlayAnimMontage(UnGrabMontage, 2);
}

void AC_Rifle::Begin_UnEquip()
{
	AttachToComponent(Owner->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket);
	bEquipped = false;
}

void AC_Rifle::End_UnEquip()
{ bEquipping = false; }

bool AC_Rifle::IsAvalibaleAim()
{
	USpringArmComponent* springArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));
	UCameraComponent*       camera = Cast<UCameraComponent>   (Owner->GetComponentByClass(UCameraComponent::StaticClass()));

	APlayerController* controller = Owner->GetController<APlayerController>();

	return springArm && camera && controller;
}

void AC_Rifle::Begin_Aim()
{
	if (!bEquipped) return;
	if (bEquipping) return;
	if (!IsAvalibaleAim()) return;

	bAiming = true;

	// controller ?? z ???????? ??????????.
	Owner->bUseControllerRotationYaw = true;
	// ???????? ???? ?????? ???? ???????? ????????.
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;

	USpringArmComponent* springArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));

	springArm->TargetArmLength = 100;
	springArm->SocketOffset = FVector(0, 30, 10);

	Timeline.PlayFromStart();

	Owner->GetController<APlayerController>()->GetHUD<ACHUD>()->Visible();
}

void AC_Rifle::End_Aim()
{
	if (!bAiming) return;

	bAiming = false;

	Owner->bUseControllerRotationYaw = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;

	USpringArmComponent* springArm = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));

	springArm->TargetArmLength = 200;
	springArm->SocketOffset = FVector(0, 60, 0);

	Timeline.ReverseFromEnd();

	Owner->GetController<APlayerController>()->GetHUD<ACHUD>()->InVisible();
}

void AC_Rifle::Begin_Fire()
{
	if (!bEquipped) return;
	if (bEquipping) return;
	if (!bAiming)   return;
	if (bFiring)    return;

	bFiring = true;

	// ???? ???? ????????
	if (bAutoFiring)
	{
		// ???? ?? ?????? Firing ?? 0.1?????? ?????????? ??????????.
		GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this,
			&AC_Rifle::Firing, 0.1, true, 0);

		return;
	}
	Firing();
}

void AC_Rifle::End_Fire()
{
	bFiring = false;

	if (bAutoFiring)
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
}

void AC_Rifle::ToggleAutoFire()
{ if (!bFiring) bAutoFiring = !bAutoFiring; }

