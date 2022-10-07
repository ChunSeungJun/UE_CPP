#include "Player/PlayerAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Owner = Cast<ACharacter>(TryGetPawnOwner());
}

void UPlayerAnim::NativeUpdateAnimation(float DelatSeconds)
{
    Super::NativeUpdateAnimation(DelatSeconds);

    if (!Owner) return;

    // GetVelocity() : ¼Ó·Â
    Speed = Owner->GetVelocity().Size2D();
    Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());
}
