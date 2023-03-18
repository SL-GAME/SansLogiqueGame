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
		bool InvertX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool InvertY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float CamSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool BobbingEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float BobbingSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FString TutoMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool ToggleSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool ToggleCrouch;

	// Video settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
		float Brightness;
	
	// Audio settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float GlobalVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float SoundVolume;
};
