// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "FPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ControllablePawn.h"
#include "Camera/CameraComponent.h"

void AMyPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Let's go player controller 3"));

	FActorSpawnParameters SpawnParams;

	myPlayer = Cast<AFPCharacter>(GetPawn());

	//PortalManager = nullptr;
	//PortalManager = GetWorld()->SpawnActor<ASLPortalManager>(ASLPortalManager::StaticClass(),
	//	FVector::ZeroVector,
	//	FRotator::ZeroRotator,
	//	SpawnParams);
	//PortalManager->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//PortalManager->SetControllerOwner(this);
}

void AMyPlayerController::AddTempCamera(UCameraComponent* _TempCamera)
{
	TempCamera = _TempCamera;
	isTemp = true;
}

void AMyPlayerController::RemoveTempCamera()
{
	TempCamera = nullptr;
	isTemp = true;
}

FMatrix AMyPlayerController::GetCameraProjectionMatrix()
{
	FMatrix ProjectionMatrix;

	if (GetLocalPlayer() != nullptr)
	{
		FSceneViewProjectionData PlayerProjectionData;

		GetLocalPlayer()->GetProjectionData(GetLocalPlayer()->ViewportClient->Viewport,
			PlayerProjectionData);

		ProjectionMatrix = PlayerProjectionData.ProjectionMatrix;
	}

	return ProjectionMatrix;
}

UCameraComponent* AMyPlayerController::GetCurrentCamera() {

	APawn* CurrentPawn = GetPawn();

	if(isTemp && TempCamera->IsValidLowLevel())
		return TempCamera;

	if (!CurrentPawn)
		return nullptr;

	AFPCharacter* CurrentPlayer = Cast<AFPCharacter>(CurrentPawn);
	if (CurrentPlayer) {
		return CurrentPlayer->GetFirstPersonCameraComponent();
	}
	else {
		AControllablePawn* CurrentControllable = Cast<AControllablePawn>(CurrentPawn);
		if (CurrentControllable)
			return CurrentControllable->GetCameraComponent();
	}
	
	return nullptr;
}

void AMyPlayerController::AsyncLevelLoad(const FString& LevelDir, const FString& LevelName)
{
	LevelToLoad = LevelName;

	LoadPackageAsync(LevelDir + LevelName,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
					OnLoadPackageSucceed();  //AsyncLevelLoadFinished(LevelName);
			}
		),
		0, PKG_ContainsMap);
}

void AMyPlayerController::LevelLoadingEnd_Implementation()
{
}

void AMyPlayerController::OnLoadPackageSucceed()
{
	// cLoadTimerHandler is a FTimeHandler
	GetWorld()->GetTimerManager().SetTimer(cLoadTimerHandler, this, &AMyPlayerController::LevelLoadingEnd, 3.0f, false);
}


void AMyPlayerController::MoveToLoadedLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*LevelToLoad));
}