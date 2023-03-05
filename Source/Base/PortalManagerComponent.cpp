// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalManagerComponent.h"
#include "EngineUtils.h"
#include "Portal.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Tools.h"

// Sets default values for this component's properties
UPortalManagerComponent::UPortalManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
	MinDistance = 5000.0f;
	// ...
}


// Called when the game starts
void UPortalManagerComponent::BeginPlay()
{
	Super::BeginPlay();

    //for (TActorIterator<APortal>ActorItr(GetWorld()); ActorItr; ++ActorItr)
    //{
	//	PortalsInScene.Add(*ActorItr);
    //}

	// ...
	
}


// Called every frame
void UPortalManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdatePortalsInWorld();
	// ...
}

void UPortalManagerComponent::UpdatePortalsInWorld() {

	AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
		return;

	FVector PlayerLocation = PC->GetCurrentCamera()->GetComponentLocation();
	
	float Distance = MinDistance;
	APortal* ActivePortal = nullptr;

	for (TActorIterator<APortal>Portal(GetWorld()); Portal; ++Portal)
	{
		Portal->SetIsActive(false);
		if (!Portal->isAlwaysActive && Portal->IsPortalOnViewPort(PC)) {
			float NewDistance = FMath::Abs(FVector::Dist(PlayerLocation, Portal->GetActorLocation()));
			if (!OnlyNearest)
				Portal->SetIsActive(NewDistance < MinDistance);
			else {
				if (NewDistance < Distance) {
					Distance = NewDistance;
					ActivePortal = *Portal;
				}
			}
		}
	}

	//for (auto Portal : PortalsInScene) {
	//	if (!Portal->isAlwaysActive) {
	//		float NewDistance = FMath::Abs(FVector::Dist(PlayerLocation, Portal->GetActorLocation()));
	//		if(!OnlyNearest)
	//			Portal->SetIsActive(NewDistance < MinDistance);
	//		else {
	//			Portal->SetIsActive(false);
	//			if (NewDistance < Distance) {
	//				Distance = NewDistance;
	//				ActivePortal = Portal;
	//			}
	//		}
	//	}
	//}

	if (OnlyNearest && ActivePortal != nullptr)
		ActivePortal->SetIsActive(true);

}


