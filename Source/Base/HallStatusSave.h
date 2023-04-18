// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HallStatusSave.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPortalHall : uint8 {
	VE_DayForest       UMETA(DisplayName = "Day Foret"),
	VE_Abstract      UMETA(DisplayName = "Abstract"),
	VE_NightForest        UMETA(DisplayName = "Night Forest"),
	VE_BackCorridor      UMETA(DisplayName = "Back Corridor"),
};


UCLASS()
class BASE_API UHallStatusSave : public USaveGame
{
	GENERATED_BODY()

public :
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Status")
	bool rockIsOnFloor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	bool controllerPickedUp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	EPortalHall currentPortal = EPortalHall::VE_DayForest;

};
