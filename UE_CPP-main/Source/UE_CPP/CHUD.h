#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class UE_CPP_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;
	// UTexture2D : 텍스처 에셋입니다.

private :
	bool bDraw = false;
	FLinearColor Color = FLinearColor::White;

public :
	ACHUD();

	// 화면에 HUD 를 그리는 기능을 추가합니다.
	virtual void DrawHUD() override;

public :
	FORCEINLINE void   Visible() { bDraw = true;  }
	FORCEINLINE void InVisible() { bDraw = false; }

	FORCEINLINE void  EnableTarget() { Color = FLinearColor::Red;   }
	FORCEINLINE void DisableTarget() { Color = FLinearColor::White; }
};
