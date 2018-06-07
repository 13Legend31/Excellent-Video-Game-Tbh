// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelPlayer.h"


// Sets default values
ALevelPlayer::ALevelPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("LevelPlayerMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("LevelPlayerSpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("LevelPlayerCamera");
	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	QObject = nullptr;
	EObject = nullptr;
	IObject = nullptr;
	PObject = nullptr;
	QHoldObject = nullptr;
	EHoldObject = nullptr;
	IHoldObject = nullptr;
	PHoldObject = nullptr;
	SpaceBarHoldObject = nullptr;
	HitCounter = 0;
	Combo = 0;

	//Hold
	DeltaTime = 0.0f;
	HoldRewardThreshold = 0.1f;
	HoldInitialRewardTime = 0.08f;
	QHoldTime = 0.0f;
	EHoldTime = 0.0f;
	IHoldTime = 0.0f;
	PHoldTime = 0.0f;
	SpaceBarHoldTime = 0.0f;
	QTimeLeftToPress = 0.0f;
	ETimeLeftToPress = 0.0f;
	ITimeLeftToPress = 0.0f;
	PTimeLeftToPress = 0.0f;
	SpaceBarTimeLeftToPress = 0.0f;
	WasQPressed = false;
	WasEPressed = false;
	WasIPressed = false;
	WasPPressed = false;
	WasSpaceBarPressed = false;

	// Animation
	GlowTime = 0.1f;
	QSensorGlowTime = 0.0f;
	ESensorGlowTime = 0.0f;
	ISensorGlowTime = 0.0f;
	PSensorGlowTime = 0.0f;
	SpaceBarSensorGlowTime = 0.0f;
}

// Called when the game starts or when spawned
void ALevelPlayer::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void ALevelPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->DeltaTime = DeltaTime;
	// Reduce TimeLeftToPress variables
	// if TimeLeftToPress is 0, reset HitCounter because player missed timing
	if (QTimeLeftToPress > 0.0f) {
		QTimeLeftToPress -= DeltaTime;
		if (QTimeLeftToPress <= 0.0f && !WasQPressed) 
			Punish();
	}
	if (ETimeLeftToPress > 0.0f) {
		ETimeLeftToPress -= DeltaTime;
		if (ETimeLeftToPress <= 0.0f && !WasEPressed) 
			Punish();
	}
	if (ITimeLeftToPress > 0.0f) {
		ITimeLeftToPress -= DeltaTime;
		if (ITimeLeftToPress <= 0.0f && !WasIPressed) 
			Punish();
	}
	if (PTimeLeftToPress > 0.0f) {
		PTimeLeftToPress -= DeltaTime;
		if (PTimeLeftToPress <= 0.0f && !WasPPressed) 
			Punish();
	}
	if (SpaceBarTimeLeftToPress > 0.0f) {
		SpaceBarTimeLeftToPress -= DeltaTime;
		if (SpaceBarTimeLeftToPress <= 0.0f && !WasSpaceBarPressed) 
			Punish();
	}

	// Update HoldTime (Multiplier System)
	if (WasQPressed) {
		QHoldTime += DeltaTime;
		if (QHoldTime > HoldRewardThreshold) {
			Reward();
			QHoldTime = 0.0f;
		}
	}
	if (WasEPressed) {
		EHoldTime += DeltaTime;
		if (EHoldTime >HoldRewardThreshold) {
			Reward();
			EHoldTime = 0.0f;
		}
	}	
	if (WasIPressed) {
		IHoldTime += DeltaTime;
		if (IHoldTime > HoldRewardThreshold) {
			Reward();
			IHoldTime = 0.0f;
		}
	}
	if (WasPPressed) {
		PHoldTime += DeltaTime;
		if (PHoldTime >HoldRewardThreshold) {
			Reward();
			PHoldTime = 0.0f;
		}
	}
	if (WasSpaceBarPressed) {
		SpaceBarHoldTime += DeltaTime;
		if (SpaceBarHoldTime > HoldRewardThreshold) {
			Reward();
			SpaceBarHoldTime = 0.0f;
		}
	}

	// Animation
	if (QSensorGlowTime > 0.0f) 
		QSensorGlowTime -= DeltaTime;
	if (ESensorGlowTime > 0.0f)
		ESensorGlowTime -= DeltaTime;
	if (ISensorGlowTime > 0.0f)
		ISensorGlowTime -= DeltaTime;
	if (PSensorGlowTime > 0.0f)
		PSensorGlowTime -= DeltaTime;
	if (SpaceBarSensorGlowTime > 0.0f)
		SpaceBarSensorGlowTime -= DeltaTime;
}

// Called to bind functionality to input
void ALevelPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Q", IE_Pressed, this, &ALevelPlayer::QPressed);
	InputComponent->BindAction("Q", IE_Released, this, &ALevelPlayer::QReleased);
	InputComponent->BindAction("E", IE_Pressed, this, &ALevelPlayer::EPressed);
	InputComponent->BindAction("E", IE_Released, this, &ALevelPlayer::EReleased);
	InputComponent->BindAction("I", IE_Pressed, this, &ALevelPlayer::IPressed);
	InputComponent->BindAction("I", IE_Released, this, &ALevelPlayer::IReleased);
	InputComponent->BindAction("P", IE_Pressed, this, &ALevelPlayer::PPressed);
	InputComponent->BindAction("P", IE_Released, this, &ALevelPlayer::PReleased);
	InputComponent->BindAction("SpaceBar", IE_Pressed, this, &ALevelPlayer::SpaceBarPressed);
	InputComponent->BindAction("SpaceBar", IE_Released, this, &ALevelPlayer::SpaceBarReleased);
}
void ALevelPlayer::QPressed() {
	if (QObject) {
		QObject->Destroy();
		QObject = nullptr;
		Reward();
		// animation
		QSensorGlowTime = GlowTime;
	}
	else if (QHoldObject && !WasQPressed && QTimeLeftToPress > 0.0f) {
		WasQPressed = true; 
		QHoldTime += HoldInitialRewardTime;
		QTimeLeftToPress = 0.0f;
	}
	else {
		Punish();
	}
}
void ALevelPlayer::QReleased() {
	// If object is still there when Q released, then punish player with following code
	if (QHoldObject) {
		Punish();
		QHoldTime = 0.0f;
		WasQPressed = false;
	}
}
void ALevelPlayer::EPressed() {
	if (EObject) {
		EObject->Destroy();
		EObject = nullptr;
		Reward();
		// animation
		ESensorGlowTime = GlowTime;
	}
	else if (EHoldObject && !WasEPressed && ETimeLeftToPress > 0.0f) {
		WasEPressed = true;
		EHoldTime += HoldInitialRewardTime;
		ETimeLeftToPress = 0.0f;
	}
	else {
		Punish();
	}
}
void ALevelPlayer::EReleased() {
	WasEPressed = false;
	if (EHoldObject) {
		Punish();
		EHoldTime = 0.0f;
	}
}
void ALevelPlayer::IPressed() {
	if (IObject) {
		IObject->Destroy();
		IObject = nullptr;
		Reward();
		// animation
		ISensorGlowTime = GlowTime;
	}
	else if (IHoldObject && !WasIPressed && ITimeLeftToPress > 0.0f) {
		WasIPressed = true;
		IHoldTime += HoldInitialRewardTime;
		ITimeLeftToPress = 0.0f;
	}
	else {
		Punish();
	}
}
void ALevelPlayer::IReleased() {
	WasIPressed = false;
	if (IHoldObject) {
		Punish();
		IHoldTime = 0.0f;
	}
}
void ALevelPlayer::PPressed() {
	if (PObject) {
		PObject->Destroy();
		PObject = nullptr;
		Reward();
		// animation
		PSensorGlowTime = GlowTime;
	}
	else if (PHoldObject && !WasPPressed && PTimeLeftToPress > 0.0f) {
		WasPPressed = true;
		PHoldTime += HoldInitialRewardTime;
		PTimeLeftToPress = 0.0f;
	}
	else {
		Punish();
	}
}
void ALevelPlayer::PReleased() {
	WasPPressed = false;
	if (PHoldObject) {
		Punish();
		PHoldTime = 0.0f;
	}
}
void ALevelPlayer::SpaceBarPressed() {
	if (SpaceBarObject) {
		SpaceBarObject->Destroy();
		SpaceBarObject = nullptr;
		Reward();
		// animation
		SpaceBarSensorGlowTime = GlowTime;
	}
	else if (SpaceBarHoldObject && !WasSpaceBarPressed && SpaceBarTimeLeftToPress > 0.0f) {
		WasSpaceBarPressed = true;
		SpaceBarHoldTime += HoldInitialRewardTime;
		SpaceBarTimeLeftToPress = 0.0f;
	}
	else {
		Punish();
	}
}
void ALevelPlayer::SpaceBarReleased() {
	if (SpaceBarHoldObject) {
		Punish();
		SpaceBarHoldTime = 0.0f;
		WasSpaceBarPressed = false;
	}
}
void ALevelPlayer::Punish(){
	HitCounter = 0;
	Combo = 0;
}
void ALevelPlayer::Reward() {
	Combo++;
	if (HitCounter < 50)
		HitCounter++;
	else {
		//animation
	}
}