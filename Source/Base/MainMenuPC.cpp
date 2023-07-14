// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPC.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuPC::AsyncLevelLoad(const FString& LevelDir, const FString& LevelName)
{
	LevelToLoad = LevelName;

	LoadPackageAsync(LevelDir + LevelName,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
					LevelLoadingEnd();
			}
		),
		0, PKG_ContainsMap);
}

void AMainMenuPC::LevelLoadingEnd_Implementation()
{
}

void AMainMenuPC::MoveToLoadedLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*LevelToLoad));
}