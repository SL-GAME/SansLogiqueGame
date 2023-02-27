// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyAbilityComponent.h"
#include "DummyPawnProjectionClass.h"
#include "MainCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "DummyPawn.h"
#include "NonPosableInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UDummyAbilityComponent::UDummyAbilityComponent() : Super()
{
	distanceDropDummy = 1000;
	cooldownDummyMax = 3.0;
	isDummyCooldown = false;
	dummyUsable = false;
	leftActionUsed = false;
	dummyProjection = nullptr;
	MeshPosition = FVector(0.02f, 0.02f, -0.03f);
	MeshRotation = FVector(0.0f, -15.0f, 0.0f);
	MeshScale = FVector(0.002f, 0.002f, 0.002f);
	maxAngleValue = 43.0f;

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Characters/MainCharacter/MainCharacterComponents/Abilities/DummyAbility/dummyMeshPawn.dummyMeshPawn"));
	if (CubeVisualAsset.Succeeded()) {
		UE_LOG(LogClass, Log, TEXT("Mesh found"));
		AbilityMesh = CubeVisualAsset.Object;
	}
}

// Called when the game starts or when spawned
void UDummyAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called when component is activate
void UDummyAbilityComponent::OnActivated(UActorComponent* Component, bool Reset)
{
	Super::OnActivated(Component, Reset);

	AMainCharacter* owner = Cast<AMainCharacter>(GetOwner());
	owner->AbilityMeshHand->SetStaticMesh(AbilityMesh);
	owner->AbilityMeshHand->SetVisibility(true);

	owner->AbilityMeshHand->SetRelativeTransform(FTransform(FQuat::MakeFromEuler(MeshRotation), MeshPosition, MeshScale));
}

// Called when component is desactivate
void UDummyAbilityComponent::OnDeactivated(UActorComponent* Component)
{
	Super::OnDeactivated(Component);

	if (IsValid(dummyProjection)) {
		dummyProjection->Destroy();
	}
	leftActionUsed = false;
	AMainCharacter* owner = Cast<AMainCharacter>(GetOwner());
	owner->AbilityMeshHand->SetStaticMesh(nullptr);
	owner->AbilityMeshHand->SetVisibility(false);
}

// Shoot a ray and return target object, hit point and normal
void UDummyAbilityComponent::shootRay(AActor*& hitTarget, FVector& hitPoint, FVector& impactNormal)
{
	AMainCharacter* owner = Cast<AMainCharacter>(GetOwner());
	FVector startRay = owner->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector endRay = startRay + UKismetMathLibrary::GetForwardVector(owner->GetFirstPersonCameraComponent()->GetComponentRotation()) * distanceDropDummy;
	FHitResult hitResult;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, startRay, endRay, ECC_Visibility, CollisionParams);
	if (isHit) {
		hitTarget = hitResult.GetActor();
		hitPoint = hitResult.ImpactPoint;
		impactNormal = hitResult.ImpactNormal;
	}

}

// Return the distance of the player with the projection
float UDummyAbilityComponent::getDistanceWithProjection()
{
	return (dummyProjection->GetActorLocation() - GetOwner()->GetActorLocation()).Length();
}


// Give the angle between a vector and the player vector up
float UDummyAbilityComponent::getAngleWithPlayer(FVector normalOfObject)
{
	normalOfObject.Normalize();
	FVector VectorUp = GetOwner()->GetActorUpVector();
	VectorUp.Normalize();
	return FGenericPlatformMath::Acos(FVector::DotProduct(normalOfObject, VectorUp)) * (180.0 / 3.141592653589793238463);
}

// Perform an ensemble of test to place the projection and tell to the player if he can spawn the dummy
void UDummyAbilityComponent::placeProjection(AActor*& hitTarget, FVector& hitPoint, FVector& impactNormal)
{
	if (IsValid(hitTarget)) {
		if (getAngleWithPlayer(impactNormal) <= maxAngleValue) {
			FVector FvectorUpOwner = GetOwner()->GetActorUpVector();
			FRotator projectionRotation = GetOwner()->GetActorRotation();
			if (IsValid(dummyProjection)) {
				dummyProjection->SetActorLocationAndRotation(hitPoint, projectionRotation);
			}
			else {
				if (IsValid(projectionToSpawn)) {
					ADummyPawnProjectionClass* item = GetWorld()->SpawnActor<ADummyPawnProjectionClass>(projectionToSpawn, hitPoint, projectionRotation, FActorSpawnParameters());
					if (item) {
						dummyProjection = item;
						dummyProjection->SetActorScale3D(GetOwner()->GetActorScale3D());
					}
				}
			}
			if (IsValid(dummyProjection)) {
				if (!hitTarget->GetClass()->ImplementsInterface(UNonPosableInterface::StaticClass()) && getDistanceWithProjection() > 125.0f && !isDummyCooldown && !dummyProjection->collisioned && getAngleWithPlayer(impactNormal) <= 5)
					dummyUsable = true;
				else
					dummyUsable = false;
			}
		} else
			destroyProjectionNewRay();
	}
	else
		destroyProjectionNewRay();
}

// Destroy the projection if it exist but new ray doesnt hit actor or with bad angle
void UDummyAbilityComponent::destroyProjectionNewRay() {
	if (IsValid(dummyProjection)) {
		dummyProjection->Destroy();
		dummyUsable = false;
	}
}

// Spawn the dummy and return true if it's worked
bool UDummyAbilityComponent::spawnDummy()
{
	if (IsValid(dummyProjection) && dummyUsable) {
		FRotator rotation = dummyProjection->GetActorRotation();
		FVector location = dummyProjection->GetActorLocation() + 100 * GetOwner()->GetActorUpVector();
		if (IsValid(dummyToSpawn)) {
			ADummyPawn* item = GetWorld()->SpawnActor<ADummyPawn>(dummyToSpawn, location, rotation, FActorSpawnParameters());
			if (item) {
				item->SetActorScale3D(dummyProjection->GetActorScale3D());
				for (TObjectIterator<ADummyPawn> Itr; Itr; ++Itr)
					if (Itr->GetActorNameOrLabel() != item->GetActorNameOrLabel())
						Itr->Destroy();
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}else
		return false;
}


// Called every frame
void UDummyAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (leftActionUsed) {
		AActor* hitTarget = nullptr;
		FVector hitPoint;
		FVector impactNormal;
		shootRay(hitTarget, hitPoint, impactNormal);
		placeProjection(hitTarget, hitPoint, impactNormal);
	}
}

// Called when leftAction is pressed
void UDummyAbilityComponent::LeftActionPressed()
{
	Super::LeftActionPressed();
	leftActionUsed = true;
}

// Called when leftAction is released
void UDummyAbilityComponent::LeftActionReleased()
{
	Super::LeftActionReleased();
	leftActionUsed = false;
	if (IsValid(dummyProjection)) {
		dummyProjection->Destroy();
	}
}

// Called when rightAction is pressed
void UDummyAbilityComponent::RightActionPressed()
{
	Super::RightActionPressed();

	bool spawned = spawnDummy();
	if (spawned) {
		isDummyCooldown = true;
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UDummyAbilityComponent::RightActionPressedDelayed, cooldownDummyMax);
	}
	
}

// Called after a few delay after rightAction pressed
void UDummyAbilityComponent::RightActionPressedDelayed()
{
	isDummyCooldown = false;
}


// Called when rightAction is released
void UDummyAbilityComponent::RightActionReleased()
{
}


