// Fill out your copyright notice in the Description page of Project Settings.


#include "SansLogiqueInstance.h"
#include "SettingsSave.h"
#include "Engine.h"

void USansLogiqueInstance::Init()
{
	LoadSettings();
}

void USansLogiqueInstance::SaveSettings(FVector PlayerLocation, int32 Score)
{
	UGameplayStatics::SaveGameToSlot(SettingsData, SettingsSaveSlot, 0);
}

USettingsSave* USansLogiqueInstance::LoadSettings()
{
	// if settings save already loaded return it
	if(SettingsData != nullptr)
		return SettingsData;

	// else load settings save
	SettingsData = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot(SettingsSaveSlot, 0));

	// if not settings save exist
	if (SettingsData != nullptr)
		return SettingsData;

	// create it
	SettingsData = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(SettingsData, SettingsSaveSlot, 0);

	return SettingsData;
}
