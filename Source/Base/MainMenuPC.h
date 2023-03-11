// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPC.generated.h"

/**
 * 
 */
UCLASS()
class BASE_API AMainMenuPC : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Async Level Loading")
	void AsyncLevelLoad(const FString& LevelDir, const FString& LevelName);

private:
	void AsyncLevelLoadFinished(const FString LevelName);
	
};
