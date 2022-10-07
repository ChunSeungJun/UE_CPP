#include "02_Log/C01_Log.h"

AC01_Log::AC01_Log() {}

void AC01_Log::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log,     L"Log");
	UE_LOG(LogTemp, Warning, L"Warning!!!");
	UE_LOG(LogTemp, Error,   L"Error!");
	UE_LOG(LogTemp, Display, L"Display");
	// UE_LOG(LogTemp, Fatal,   L"Fatal");
}


