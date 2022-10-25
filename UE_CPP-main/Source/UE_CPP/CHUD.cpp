#include "CHUD.h"
#include "Engine/Canvas.h" // UI 를 그릴 Layer 입니다.

ACHUD::ACHUD()
{
    ConstructorHelpers::FObjectFinder<UTexture2D> texture(L"Texture2D'/Game/Textures/T_Dot.T_Dot'");
    if (texture.Succeeded()) Texture = texture.Object;
}

void ACHUD::DrawHUD()
{
    Super::DrawHUD();

    // bDraw 가 false 라면 도트를 그리지 않고 함수를 종료합니다.
    if (!bDraw) return;

    // 중앙 지점을 저장합니다.
    FVector2D center(      Canvas->ClipX * 0.5f,       Canvas->ClipY * 0.5f);
    FVector2D size  (Texture->GetSizeX() * 0.5f, Texture->GetSizeY() * 0.5f);
    FVector2D position = center - size;

    // Canvas 에 그릴 아이템을 생성합니다.
    FCanvasTileItem item(position, Texture->Resource, Color);

    // Canvas에 생성한 아이템을 그립니다.
    Canvas->DrawItem(item);
}
