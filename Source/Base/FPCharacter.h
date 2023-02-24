// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// TODO : remove include here and place it in cpp file

#include "NinjaCharacter.h"
#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GrabSystem.h"
#include "FPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCurveFloat;
class UPlayerAbilityComponent;
class UPhysicsHandleComponent;
class UPortalManagerComponent;
class UDummyAbilityComponent;

UCLASS()
class BASE_API AFPCharacter : public ANinjaCharacter
{
	GENERATED_BODY()

	// ===== CAPSULE =====

		// Capsule size
		float DefaultCapsuleSize;
		float CrouchedCapsuleSize;

	// ===== CAMERA =====

		// Spring arm component : carry on the camera
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

		// Camera component
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FPCamera;

		// Camera sensibility
		UPROPERTY(EditAnywhere, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float CameraSensibility = 1.5f;

		// Camera max vertical speed
		UPROPERTY(EditAnywhere, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float CameraMaxVSpeed = 2.5f;

		// Camera max horizontal speed
		UPROPERTY(EditAnywhere, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float CameraMaxHSpeed = 2.5f;

		// Can move camera 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		bool bCanMoveCamera = true;

		// Can move lean
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		bool bCanLean = true;

	// ===== CHARACTER =====
	
		// Character speed
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float DefaultWalkSpeed = 300;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float CrouchedWalkSpeed = 150;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float RunSpeed = 600;
		

		//Character leaning
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		float LeanSpeed = 4.0f;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		FTransform RightLeanTransform;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FPCharacter, meta = (AllowPrivateAccess = "true"))
		FTransform LeftLeanTransform;
		float LeanT = 0.0f;

		// Character movements booleans
		bool bIsCrouched = false;
		bool bIsLeaningRight = false;
		bool bIsLeaningLeft = false;
		bool bIsSprinting = false;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UPlayerAbilityComponent* CurrentAbility;

	// ===== COMPONENTS =====
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UPhysicsHandleComponent* PhysicscHandle;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UPortalManagerComponent* PMComponent;

protected:

	// ===== TIMELINES =====
		
		FTimeline T_GetUp;
		FTimeline T_Crouch;

	// ===== CURVES =====

		UPROPERTY(EditAnywhere)
		UCurveFloat* GetUpCurve;
		UPROPERTY(EditAnywhere)
		UCurveFloat* CrouchCurve;


public:
	
	// Sets default values for this character's properties
	AFPCharacter(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getter and setters
	UCameraComponent* GetFirstPersonCameraComponent() const { return FPCamera; }

	USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }

	// Character movements
	void LookUpAndDown(float);
	void LookRightAndLeft(float);
	void MoveForwardBackward(float);
	void MoveRightLeft(float);

	// Character special movements
	void Sprint();
	void CrouchDown();
	void LeanRightPressed();
	void LeanRightReleased();
	void LeanLeftPressed();
	void LeanLeftReleased();
	void LeanMovement(float);
	void CameraLean();

	// Character actions events
	void LeftActionPressed();
	void LeftActionReleased();
	void RightActionPressed();
	void RightActionReleased();

	// Timelines functions
	UFUNCTION()
		void GetUpProgress(float Value);
	UFUNCTION()
		void CrouchProgress(float Value);

	// Others functions
	void DisableCameraLag();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void EnableCameraLag();
	void SetCurrentAbility(UPlayerAbilityComponent* newAbility);
	void ToggleRunningState();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
