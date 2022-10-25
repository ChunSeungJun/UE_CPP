#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UserWidget.generated.h"

UCLASS()
class UE_CPP_API UC_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	// 연사의 온 오프를 cpp 가 아닌 블루프린트에서 구현하도록 설정합니다.
	UFUNCTION(BlueprintImplementableEvent)
		void On();
	UFUNCTION(BlueprintImplementableEvent)
		void Off();
};
