// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools.h"
#include "EngineGlobals.h"

void UTools::PrintErrorInLog(FString message) {

	UE_LOG(LogTemp, Error, TEXT("%s"), *message);
}

void UTools::PrintWarningInLog(FString message) {

	UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
}

void UTools::PrintMessageInLog(FString message) {

	UE_LOG(LogTemp, Display, TEXT("%s"), *message);
}

void UTools::PrintErrorOnScreen(FString message) {

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"), *message));
	
}

void UTools::PrintWarningOnScreen(FString message) {

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *message));

}

void UTools::PrintMessageOnScreen(FString message) {

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("%s"), *message));

}

void UTools::PrintMessageOnScreen(FString message, FColor color) {

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, color, FString::Printf(TEXT("%s"), *message));

}

bool UTools::IsInputEnabled(APawn* Target)
{
	return Target->InputEnabled() && IsValid(Target->Controller);
}

FString UTools::GetAppVersion()
{
	FString AppVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	return AppVersion;
}
