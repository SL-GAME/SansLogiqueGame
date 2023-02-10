// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilityComponent.generated.h"

class AFPCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BASE_API UPlayerAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* AbilityMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector MeshPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector MeshRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector MeshScale;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	AFPCharacter* Character;

public:	
	// Sets default values for this component's properties
	UPlayerAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnActivated(UActorComponent* Component, bool Reset);

	UFUNCTION()
	virtual void OnDeactivated(UActorComponent* Component);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerAbility")
	void OnComponentActivatedEvent(UActorComponent* Component, bool Reset);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerAbility")
	void OnComponentDeactivatedEvent(UActorComponent* Component);

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerAbility")
	void LeftActionPressedEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerAbility")
	void LeftActionReleasedEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerAbility")
	void RightActionPressedEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerAbility")
	void RightActionReleasedEvent();

public:	

	UFUNCTION(BlueprintCallable, Category = "PlayerAbility")
	virtual void LeftActionPressed();

	UFUNCTION(BlueprintCallable, Category = "PlayerAbility")
	virtual void LeftActionReleased();

	UFUNCTION(BlueprintCallable, Category = "PlayerAbility")
	virtual void RightActionPressed();

	UFUNCTION(BlueprintCallable, Category = "PlayerAbility")
	virtual void RightActionReleased();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
