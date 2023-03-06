// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControllablePawn.generated.h"

class UCameraComponent;


UCLASS()
class BASE_API AControllablePawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ControllablePawn, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ControllablePawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ControllablePawn, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;


public:
	// Sets default values for this pawn's properties
	AControllablePawn();

	// Getter and setters
	UCameraComponent* GetCameraComponent() const { return Camera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
