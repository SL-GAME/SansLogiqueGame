// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"
#include "Portal.generated.h"


class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventPlayerGetTeleported);

UCLASS()
class BASE_API APortal : public AActor
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere)
		bool isActive;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<USceneComponent*> PortalCorners;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* BackFacingScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PortalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* SceneCapture;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextureRenderTarget2D* PortalTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APortal* LinkedPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PortalQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAlwaysActive;

	AMyPlayerController* ControllerOwner;

	TArray<AFPCharacter*> ActorsInPortal;

	
public:	
	// Sets default values for this actor's properties
	APortal();

	//Render target to use to display the portal
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Proto|Portal")
	void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Proto|Portal")
	void SetRTT(UTextureRenderTarget2D* RenderTexture);

	void UpdatePortal();

	bool GetIsActive();

	void SetIsActive(bool newIsActive);

	UFUNCTION()
	bool IsPortalOnViewPort(AMyPlayerController* PC);

	bool IsPlayerLookingAtPortal(AMyPlayerController* PC);

	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FEventPlayerGetTeleported OnPlayerCrossPortal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitSceneCapture();

	void InitTextureTarget();

	void CheckIfPlayerShouldTeleport(AFPCharacter* Player);

	void TeleportPlayer(AFPCharacter* Player);

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
