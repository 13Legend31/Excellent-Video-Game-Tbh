// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayer.h"


// Sets default values
AMenuPlayer::AMenuPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MenuPlayerMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("MenuPlayerSpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("MenuPlayerCameraComponent");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMenuPlayer::BeginPlay()
{
	Super::BeginPlay();
	PController = GetWorld()->GetFirstPlayerController();
	if (PController) {
		PController->bShowMouseCursor = true;
		PController->bEnableClickEvents = true;
	}
}

// Called every frame
void AMenuPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMenuPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

