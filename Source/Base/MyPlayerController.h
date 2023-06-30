// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AFPCharacter;
/**
 * 
 */
UCLASS()
class BASE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	//ASLPortalManager* PortalManager;

	//FMatrix GetCameraProjectionMatrix();

	AFPCharacter* myPlayer;

	UPROPERTY()
	UCameraComponent* TempCamera;

	UPROPERTY()
	bool isTemp;

	UFUNCTION(BlueprintCallable)
	void AddTempCamera(UCameraComponent* _TempCamera);

	UFUNCTION(BlueprintCallable)
	void RemoveTempCamera();

	FMatrix GetCameraProjectionMatrix();

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCurrentCamera();

public:

	UFUNCTION(BlueprintCallable, Category = "Async Level Loading")
		void AsyncLevelLoad(const FString& LevelDir, const FString& LevelName);

private:
	void AsyncLevelLoadFinished(const FString LevelName);
	

protected:
	virtual void BeginPlay() override;
};
