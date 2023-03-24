// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SansLogiqueInstance.generated.h"

class USettingsSave;
class UPlayerSave;
class UHallStatusSave;

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

	UPROPERTY()
	FString HallStatusSaveSlot = "Hall";

	UPROPERTY()
	UHallStatusSave* HallData;

	UPROPERTY()
	FString PlayerSaveSlot = "Player";

	UPROPERTY()
	UPlayerSave* PlayerData;

public:

	UFUNCTION(BlueprintCallable, Category = "Settings Save")
	void SaveSettings();

	UFUNCTION(BlueprintPure, Category = "Settings Save")
	USettingsSave* LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Hall Status Save")
	void SaveHallData();

	UFUNCTION(BlueprintPure, Category = "Hall Status Save")
	UHallStatusSave* LoadHallData();

	UFUNCTION(BlueprintCallable, Category = "Player Save")
	void SavePlayerData();

	UFUNCTION(BlueprintPure, Category = "Player Save")
	UPlayerSave* LoadPlayerData();

	UFUNCTION(BlueprintCallable, Category = "New Save")
	void CreateDefaultDataSave();
};
