// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPC.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuPC::AsyncLevelLoad(const FString& LevelDir, const FString& LevelName)
{
	LoadPackageAsync(LevelDir + LevelName,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
				AsyncLevelLoadFinished(LevelName);
			}
		),
		0, PKG_ContainsMap);
}

void AMainMenuPC::AsyncLevelLoadFinished(const FString LevelName)
{
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
}