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

	UPROPERTY()
	FString SettingsSaveSlot = "Settings";

	UPROPERTY()
	USettingsSave* SettingsData;

public:

	UFUNCTION(BlueprintCallable, Category = "Settings Save")
	void SaveSettings();

	UFUNCTION(BlueprintPure, Category = "Settings Save")
	USettingsSave* LoadSettings();

};
