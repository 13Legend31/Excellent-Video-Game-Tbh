// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DontCrash.h"
#include "LevelPlayer.generated.h"

UCLASS()
class DONTCRASH_API ALevelPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALevelPlayer();
	UFUNCTION(BlueprintCallable) void Punish();
	UFUNCTION(BlueprintCallable) void Reward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UCameraComponent* Camera;	

	// Inputs
	void QPressed();
	void EPressed();
	void IPressed();
	void PPressed();
	void SpaceBarPressed();
	void QReleased();
	void EReleased();
	void IReleased();
	void PReleased();
	void SpaceBarReleased();

	// Moving actor references
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* QObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* EObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* IObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* PObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* SpaceBarObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* QHoldObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* EHoldObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* IHoldObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* PHoldObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* SpaceBarHoldObject;
	
	// HUD variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int HitCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Combo;

	// Hold Object Counter Variables
protected:
	float DeltaTime;
	float HoldRewardThreshold;
	float HoldInitialRewardTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float QHoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float EHoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float IHoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PHoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpaceBarHoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool WasQPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool WasEPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool WasIPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool WasPPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool WasSpaceBarPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float QTimeLeftToPress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ETimeLeftToPress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ITimeLeftToPress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PTimeLeftToPress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpaceBarTimeLeftToPress;

	// Sensor Animation
protected:
	float GlowTime;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float QSensorGlowTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float ESensorGlowTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float ISensorGlowTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float PSensorGlowTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float SpaceBarSensorGlowTime;
};
