// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SansLogiqueInstance.generated.h"

class USettingsSave;

/**
 * 
 */
UCLASS()
class BASE_API USansLogiqueInstance : public UGameInstance
{
	GENERATED_BODY()

	void Init() override;

	FString SettingsSaveSlot = "Settings";

	USettingsSave* SettingsData;

public:

	UFUNCTION(BlueprintCallable, Category = "Settings Save")
	void SaveSettings(FVector PlayerLocation, int32 Score);

	UFUNCTION(BlueprintCallable, Category = "Settings Save")
	USettingsSave* LoadSettings();

};
