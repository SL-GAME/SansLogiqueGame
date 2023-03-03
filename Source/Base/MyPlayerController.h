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

	FMatrix GetCameraProjectionMatrix();

	UFUNCTION()
	UCameraComponent* GetCurrentCamera();
	

protected:
	virtual void BeginPlay() override;
};
