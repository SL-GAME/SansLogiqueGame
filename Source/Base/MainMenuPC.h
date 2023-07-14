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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level to load")
	FString LevelToLoad;

	UFUNCTION(BlueprintCallable, Category = "Async Level Loading")
	void AsyncLevelLoad(const FString& LevelDir, const FString& LevelName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Async Level Loading")
	void LevelLoadingEnd();

	UFUNCTION(BlueprintCallable, Category = "Async Level Loading")
	void MoveToLoadedLevel();
	
};
