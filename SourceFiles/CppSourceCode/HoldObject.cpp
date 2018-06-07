// Fill out your copyright notice in the Description page of Project Settings.

#include "HoldObject.h"


// Sets default values
AHoldObject::AHoldObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>("HoldObjectMainMesh");
	Tail = CreateDefaultSubobject<UStaticMeshComponent>("HoldObjectTail");
	RootComponent = MainMesh;
	Tail->SetupAttachment(MainMesh);
}

// Called when the game starts or when spawned
void AHoldObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoldObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoldObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

