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
	
	AMainCharacter(const FObjectInitializer& ObjectInitializer);
};
