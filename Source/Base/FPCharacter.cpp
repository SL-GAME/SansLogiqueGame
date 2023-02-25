// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "PlayerAbilityComponent.h"
#include "Camera/CameraComponent.h"
//#include "Components/TimelineComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PortalManagerComponent.h"
#include "DummyAbilityComponent.h"
#include "GrabSystem.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Tools.h"
#include "CustomCharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFPCharacter::AFPCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Spring Arm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetWorldLocation(FVector(0, 0, 10)); 
	SpringArm->TargetArmLength = 0;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 20;
	SpringArm->CameraRotationLagSpeed = 20;
	SpringArm->bUsePawnControlRotation = false;

	// Create CameraComponent    
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(SpringArm);
	FPCamera->SetWorldLocation(FVector(0, 0, 60));
	FPCamera->bUsePawnControlRotation = true;

	// Create PhysicsHandle component
	PhysicscHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	PhysicscHandle->LinearDamping = 50;

	// Create PortalManager component
	PMComponent = CreateDefaultSubobject<UPortalManagerComponent>(TEXT("PortalManager"));

	// Create GrabAbility component
	//GrabAbility = CreateDefaultSubobject<UGrabSystem>(TEXT("GrabAbility"));

	// Setting up speed for character
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;

	//Getting default capsule size value
	DefaultCapsuleSize = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	CrouchedCapsuleSize = DefaultCapsuleSize / 2;

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind timelines
	FOnTimelineFloat TimelineProgress;

	if (GetUpCurve) {

		TimelineProgress.BindUFunction(this, FName("GetUpProgress"));
		T_GetUp.AddInterpFloat(GetUpCurve, TimelineProgress);
		T_GetUp.SetLooping(false);
	}
	else {
		UTools::PrintErrorInLog("No GetUpCurve defined for this character.");
	}

	if (CrouchCurve) {

		TimelineProgress.BindUFunction(this, FName("CrouchProgress"));
		T_Crouch.AddInterpFloat(CrouchCurve, TimelineProgress);
		T_Crouch.SetLooping(false);
	}
	else {
		UTools::PrintErrorInLog("No CrouchCurve defined for this character.");
	}

}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Timelines
	T_Crouch.TickTimeline(DeltaTime);
	T_GetUp.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Character default actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	// Camera movements inputs
	PlayerInputComponent->BindAxis("LookUp/LookDown", this, &AFPCharacter::LookUpAndDown);
	PlayerInputComponent->BindAxis("LookRight/LookLeft", this, &AFPCharacter::LookRightAndLeft);

	// FPCharacter movements inputs
	PlayerInputComponent->BindAxis("Forward/Backward", this, &AFPCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("Right/Left", this, &AFPCharacter::MoveRightLeft);
	PlayerInputComponent->BindAxis("Lean", this, &AFPCharacter::LeanMovement);

	// FPCharacter special movements inputs
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPCharacter::Sprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPCharacter::CrouchDown);
	PlayerInputComponent->BindAction("LeanRight", IE_Pressed, this, &AFPCharacter::LeanRightPressed);
	PlayerInputComponent->BindAction("LeanRight", IE_Released, this, &AFPCharacter::LeanRightReleased);
	PlayerInputComponent->BindAction("LeanLeft", IE_Pressed, this, &AFPCharacter::LeanLeftPressed);
	PlayerInputComponent->BindAction("LeanLeft", IE_Released, this, &AFPCharacter::LeanLeftReleased);

	// FPCharacter actions inputs
	PlayerInputComponent->BindAction("LeftAction", IE_Pressed, this, &AFPCharacter::LeftActionPressed);
	PlayerInputComponent->BindAction("LeftAction", IE_Released, this, &AFPCharacter::LeftActionReleased);
	PlayerInputComponent->BindAction("RightAction", IE_Pressed, this, &AFPCharacter::RightActionPressed);
	PlayerInputComponent->BindAction("RightAction", IE_Released, this, &AFPCharacter::RightActionReleased);

}

void AFPCharacter::LookUpAndDown(float Value)
{
	if (bCanMoveCamera) {
		Value = FMath::Clamp(Value, -CameraMaxVSpeed, CameraMaxVSpeed);
		AddControllerPitchInput(CameraSensibility * Value);
	}
}

void AFPCharacter::LookRightAndLeft(float Value)
{
	if (bCanMoveCamera) {
		Value = FMath::Clamp(Value, -CameraMaxHSpeed, CameraMaxHSpeed);
		AddControllerYawInput(CameraSensibility * Value);
	}
}

void AFPCharacter::MoveForwardBackward(float Value)
{
	// Check if character stopped moving
	if (Value == 0 && bIsSprinting) {
		ToggleRunningState();
	}

	FRotator Rot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector WorldDirection = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);
	AddMovementInput(this->GetActorForwardVector(), Value);
}

void AFPCharacter::MoveRightLeft(float Value)
{
	FRotator Rot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector WorldDirection = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);
	AddMovementInput(this->GetActorRightVector(), Value);
}

// Calcul new lean progression depending axis input value
void AFPCharacter::LeanMovement(float Value) {

	if (bCanLean && FMath::Abs(Value) > 0.1f) {
		LeanT += Value * LeanSpeed * FApp::GetDeltaTime();
		LeanT = FMath::Clamp(LeanT, -1.0f, 1.0f);
	}
	else {
		LeanT += FMath::Sign(LeanT) * LeanSpeed * FApp::GetDeltaTime() * -1.0f;
		if (FMath::Abs(LeanT) < LeanReset)
			LeanT = 0.0f;
	}

	if(LeanT != PreviousLeanT)
		CameraLean(MaxLeanIteration);

	PreviousLeanT = LeanT;
}

// Apply lean progression to the camera
void AFPCharacter::CameraLean(int iteration) {
	if (iteration < 0)
		return;

	FTransform newTransform;

	if (LeanT >= 0.0f) 
		newTransform = UKismetMathLibrary::TLerp(FTransform::Identity, RightLeanTransform, LeanT);
	else 
		newTransform = UKismetMathLibrary::TLerp(FTransform::Identity, RightLeanTransform, LeanT);

	FPCamera->SetRelativeTransform(newTransform);

	FHitResult CollisionResult;
	const bool Collision = UKismetSystemLibrary::SphereTraceSingle(this, FPCamera->GetComponentLocation(), FPCamera->GetComponentLocation(), 16.0f, UEngineTypes::ConvertToTraceType(ECC_Camera), false, TArray<AActor*>(), EDrawDebugTrace::None, CollisionResult, true);
	if (Collision) {
		LeanT += FMath::Sign(LeanT) * LeanSpeed * FApp::GetDeltaTime() * -1.0f;
		LeanT = FMath::Clamp(LeanT, -1.0f, 1.0f);
		CameraLean(iteration - 1);
	}
}

void AFPCharacter::Sprint()
{
	if (!bIsSprinting && !IsCrouched) {
		ToggleRunningState();
	}
	else if(bIsSprinting) {
		ToggleRunningState();
	}
}

void AFPCharacter::CrouchDown()
{
	if (bIsSprinting) {
		bIsSprinting = false;
	}
	if (CrouchCurve && GetUpCurve) {
		
		if (!GetCharacterMovement()->IsFalling()) { // If the character isn't currently jumping

			if (IsCrouched) {

				GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
				T_GetUp.PlayFromStart();
				IsCrouched = false;
			}
			else {

				GetCharacterMovement()->MaxWalkSpeed = CrouchedWalkSpeed;
				T_Crouch.PlayFromStart();
				IsCrouched = true;
			}
		}
	}
	else {
		
		UTools::PrintErrorInLog("Can't use this action because a curve movement is missing.");
	}
	
}

void AFPCharacter::LeanLeftPressed() {
	
	bIsLeaningLeft = true;
	if (!bIsLeaningRight) {
		bCanMoveCamera = false;
	}
}

void AFPCharacter::LeanLeftReleased() {
	
	bIsLeaningLeft = false;
	if (!bIsLeaningRight && bCanLean) {
		bCanMoveCamera = true;
	}
}

void AFPCharacter::LeanRightPressed() {

	bIsLeaningRight = true;
	if (!bIsLeaningLeft) {
		bCanMoveCamera = false;
	}
}

void AFPCharacter::LeanRightReleased() {
	
	bIsLeaningRight = false;
	if (!bIsLeaningLeft && bCanLean) {
		bCanMoveCamera = true;
	}
}

//Disable camera lag caused by spring arm
void AFPCharacter::DisableCameraLag()
{
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	EnableCameraLag();
}

void AFPCharacter::SetCurrentAbility(UPlayerAbilityComponent* newAbility)
{
	CurrentAbility = newAbility;
}

void AFPCharacter::ToggleRunningState()
{
	if (bIsSprinting) {
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
	else {
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}	
}

void AFPCharacter::LeftActionPressed()
{
	// Calling PlayerAbilityComponent LeftActionPressed
	if (CurrentAbility) {
		CurrentAbility->LeftActionPressed();
	}
	else {
		UTools::PrintErrorInLog("This character doesn't have any ability activated.");
	}
}

void AFPCharacter::LeftActionReleased()
{
	// Calling PlayerAbilityComponent LeftActionReleased
	if (CurrentAbility) {
		CurrentAbility->LeftActionReleased();
	}
	else {
		UTools::PrintErrorInLog("This character doesn't have any ability activated.");
	}
}

void AFPCharacter::RightActionPressed()
{
	// Calling PlayerAbilityComponent RightActionPressed
	if (CurrentAbility) {
		CurrentAbility->RightActionPressed();
	}
	else {
		UTools::PrintErrorInLog("This character doesn't have any ability activated.");
	}
}

void AFPCharacter::RightActionReleased()
{
	// Calling PlayerAbilityComponent RightActionReleased
	if (CurrentAbility) {
		CurrentAbility->RightActionReleased();
	}
	else {
		UTools::PrintErrorInLog("This character doesn't have any ability activated.");
	}
}

//Enable camera lag caused by spring arm
void AFPCharacter::EnableCameraLag_Implementation()
{
}

// Called by timeline to have a prgressive get up movement
void AFPCharacter::GetUpProgress(float Value)
{
	float NewValue = FMath::Lerp(CrouchedCapsuleSize, DefaultCapsuleSize, Value);
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewValue);
}

// Called by timeline to have a prgressive crouch movement
void AFPCharacter::CrouchProgress(float Value)
{
	float NewValue = FMath::Lerp(DefaultCapsuleSize, CrouchedCapsuleSize, Value);
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewValue);
}

