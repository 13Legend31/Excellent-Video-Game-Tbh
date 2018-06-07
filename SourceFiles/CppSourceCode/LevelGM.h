// Made By Larry

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DontCrash.h"
#include "LevelGM.generated.h"

/**
 * 
 */
UCLASS()
class DONTCRASH_API ALevelGM : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALevelGM();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UAudioComponent* Song;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Time;
};
