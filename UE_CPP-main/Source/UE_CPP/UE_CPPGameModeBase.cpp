#include "UE_CPPGameModeBase.h"
#include "GameFramework/HUD.h"

AUE_CPPGameModeBase::AUE_CPPGameModeBase()
{
    // 게임의 기본 캐릭터를 설정합니다.
    ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/Player/BP_Player.BP_Player_C'");
    if (pawn.Succeeded()) DefaultPawnClass = pawn.Class;

    // 게임의 기본 HUD 를 설정합니다.
    ConstructorHelpers::FClassFinder<AHUD> hud(L"Blueprint'/Game/BP_HUD.BP_HUD_C'");
    if (hud.Succeeded()) HUDClass = hud.Class;
}