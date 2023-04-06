// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityComponent.h"
#include "FPCharacter.h"

// Sets default values for this component's properties
UPlayerAbilityComponent::UPlayerAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AFPCharacter>(GetOwner());
	this->OnComponentActivated.AddDynamic(this, &UPlayerAbilityComponent::OnActivated);
	this->OnComponentDeactivated.AddDynamic(this, &UPlayerAbilityComponent::OnDeactivated);

	if (bAutoActivate)
		OnActivated(this, true);
	// ...
	
}

void UPlayerAbilityComponent::OnActivated(UActorComponent* Component, bool Reset)
{
	Character->SetCurrentAbility(this);
	SetComponentTickEnabled(true);
	UE_LOG(LogTemp, Warning, TEXT("TICK ENABLED"));
	OnComponentActivatedEvent(Component, Reset);
}

void UPlayerAbilityComponent::OnDeactivated(UActorComponent* Component)
{
	Character->SetCurrentAbility(nullptr);
	SetComponentTickEnabled(false);
	UE_LOG(LogTemp, Warning, TEXT("TICK DISABLED"));
	OnComponentDeactivatedEvent(Component);
}

void UPlayerAbilityComponent::LeftActionPressed()
{
	LeftActionPressedEvent();
}

void UPlayerAbilityComponent::LeftActionReleased()
{
	LeftActionReleasedEvent();
}

void UPlayerAbilityComponent::RightActionPressed()
{
	RightActionPressedEvent();
}

void UPlayerAbilityComponent::RightActionReleased()
{
	RightActionReleasedEvent();
}

void UPlayerAbilityComponent::OnComponentActivatedEvent_Implementation(UActorComponent* Component, bool Reset){}
void UPlayerAbilityComponent::OnComponentDeactivatedEvent_Implementation(UActorComponent* Component){}
void  UPlayerAbilityComponent::LeftActionPressedEvent_Implementation() {};
void  UPlayerAbilityComponent::RightActionPressedEvent_Implementation() {};
void  UPlayerAbilityComponent::LeftActionReleasedEvent_Implementation() {};
void  UPlayerAbilityComponent::RightActionReleasedEvent_Implementation() {};
void UPlayerAbilityComponent::ShowAbilityEvent_Implementation() {};
void UPlayerAbilityComponent::HideAbilityEvent_Implementation() {};

// Called every frame
void UPlayerAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
