// Made By Larry

#include "LevelGM.h"

// Constructor
ALevelGM::ALevelGM() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;

	Song = CreateDefaultSubobject<UAudioComponent>("LevelGM_Song");
	RootComponent = Song;
	Time = 0.0f;
}

