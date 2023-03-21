// Fill out your copyright notice in the Description page of Project Settings.


#include "SansLogiqueInstance.h"
#include "SettingsSave.h"
#include "HallStatusSave.h"
#include "PlayerSave.h"
#include "Engine.h"

void USansLogiqueInstance::Init()
{
	LoadSettings();
}

void USansLogiqueInstance::SaveSettings()
{
	if(IsValid(SettingsData))
		UGameplayStatics::SaveGameToSlot(SettingsData, SettingsSaveSlot, 0);
	else {
		LoadSettings();
		UGameplayStatics::SaveGameToSlot(SettingsData, SettingsSaveSlot, 0);
	}
}

USettingsSave* USansLogiqueInstance::LoadSettings()
{
	// if settings save already loaded return it
	if(IsValid(SettingsData))
		return SettingsData;

	// else load settings save
	SettingsData = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot(SettingsSaveSlot, 0));

	// if not settings save exist
	if (IsValid(SettingsData))
		return SettingsData;

	// create it
	SettingsData = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(SettingsData, SettingsSaveSlot, 0);

	return SettingsData;
}

void USansLogiqueInstance::SaveHallData()
{
	if (IsValid(HallData))
		UGameplayStatics::SaveGameToSlot(HallData, HallStatusSaveSlot, 0);
	else
	{
		LoadHallData();
		UGameplayStatics::SaveGameToSlot(HallData, HallStatusSaveSlot, 0);
	}
		

}

UHallStatusSave* USansLogiqueInstance::LoadHallData()
{
	// if settings save already loaded return it
	if (IsValid(HallData))
		return HallData;

	// else load settings save
	HallData = Cast<UHallStatusSave>(UGameplayStatics::LoadGameFromSlot(HallStatusSaveSlot, 0));

	// if not settings save exist
	if (IsValid(HallData))
		return HallData;

	// create it
	HallData = Cast<UHallStatusSave>(UGameplayStatics::CreateSaveGameObject(UHallStatusSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(HallData, HallStatusSaveSlot, 0);

	return HallData;
}

void USansLogiqueInstance::SavePlayerData()
{
	if (IsValid(PlayerData))
		UGameplayStatics::SaveGameToSlot(PlayerData, PlayerSaveSlot, 0);
	else {
		LoadPlayerData();
		UGameplayStatics::SaveGameToSlot(PlayerData, PlayerSaveSlot, 0);
	}
}

UPlayerSave* USansLogiqueInstance::LoadPlayerData()
{
	// if settings save already loaded return it
	if (IsValid(PlayerData))
		return PlayerData;

	// else load settings save
	PlayerData = Cast<UPlayerSave>(UGameplayStatics::LoadGameFromSlot(PlayerSaveSlot, 0));

	// if not settings save exist
	if (IsValid(PlayerData))
		return PlayerData;

	// create it
	PlayerData = Cast<UPlayerSave>(UGameplayStatics::CreateSaveGameObject(UPlayerSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(PlayerData, PlayerSaveSlot, 0);

	return PlayerData;
}

void USansLogiqueInstance::CreateDefaultDataSave()
{
	HallData = Cast<UHallStatusSave>(UGameplayStatics::CreateSaveGameObject(UHallStatusSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(HallData, HallStatusSaveSlot, 0);

	PlayerData = Cast<UPlayerSave>(UGameplayStatics::CreateSaveGameObject(UPlayerSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(PlayerData, PlayerSaveSlot, 0);
}
