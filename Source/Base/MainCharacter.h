// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BASE_API AMainCharacter : public AFPCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* AbilityMeshHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MainCharacter, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandBobbingComponent;

	float HandT = 0.0f;

	//Breathing Bobbing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	float shiftAmount = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	float maxShiftX = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	float maxShiftY = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	float smoothShift = 0.5f;

	//Breathing Bobbing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandyBreathingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandzBreathingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandSpeedBreathingBobbing = 0.0f;

	//Breathing Bobbing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandyWalkingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandzWalkingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandSpeedWalkingBobbing = 0.0f;

	//Crouching Bobbing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandyCrouchingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandzCrouchingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandSpeedCrouchingBobbing = 0.0f;

	//Sprinting Bobbing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandySprintingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandzSprintingBobbing = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HandBobbing, meta = (AllowPrivateAccess = "true"))
		float HandSpeedSprintingBobbing = 0.0f;

	void HandBobbing();

	
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
