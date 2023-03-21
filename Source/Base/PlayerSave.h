// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSave.generated.h"

UENUM(BlueprintType)
enum class EWorldCheckpoint : uint8 {
	VE_CP00_Bedroom			UMETA(DisplayName = "CP00 Bedroom"),
	VE_CP01_Desert			UMETA(DisplayName = "CP01 Desert"),
	VE_CP02_Corridor1		UMETA(DisplayName = "CP02 Corridor1"),
	VE_CP03_Hall			UMETA(DisplayName = "CP03 Hall"),
	VE_CP04_NightForest		UMETA(DisplayName = "CP04 Night Forest"),
	VE_CP05_Corridor2		UMETA(DisplayName = "CP05 Corridor2")
};


/**
 * 
 */
UCLASS()
class BASE_API UPlayerSave : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Abilities")
	TArray<bool> abilities = TArray<bool>({ true, false, true, true });

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Respawn")
	EWorldCheckpoint lastCheckPoint = EWorldCheckpoint::VE_CP00_Bedroom;
};
