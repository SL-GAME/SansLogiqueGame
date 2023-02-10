// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tools.generated.h"

/**
 * 
 */
UCLASS()
class BASE_API UTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void PrintErrorInLog(FString);
	static void PrintWarningInLog(FString);
	static void PrintMessageInLog(FString);
	static void PrintErrorOnScreen(FString);
	static void PrintWarningOnScreen(FString);
	static void PrintMessageOnScreen(FString);
	static void PrintMessageOnScreen(FString, FColor);
	
};
