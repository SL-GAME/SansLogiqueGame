// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSave.generated.h"

/**
 * 
 */
UCLASS()
class BASE_API USettingsSave : public USaveGame
{
	GENERATED_BODY()

public :

	// Gameplay settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool InvertX = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool InvertY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float CamSens = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool BobbingEnable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float BobbingSens = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FString TutoMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int HintLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int HudLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool ToggleSprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool ToggleCrouch = true;

	// Video settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
		float Brightness = 0.5f;
	
	// Audio settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float GlobalVolume = 0.75f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float MusicVolume = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float SoundVolume = 1;
};
