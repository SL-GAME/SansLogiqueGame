// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "FPCharacter.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetTickGroup(ETickingGroup::TG_PostUpdateWork);
	isActive = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->Mobility = EComponentMobility::Static;

	BackFacingScene = CreateDefaultSubobject<USceneComponent>(TEXT("BackFacingScene"));
	BackFacingScene->SetupAttachment(GetRootComponent());
	BackFacingScene->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BackFacingScene->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, -180.0f)));
	BackFacingScene->Mobility = EComponentMobility::Static;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(GetRootComponent());
	PortalMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	PortalMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	PortalMesh->Mobility = EComponentMobility::Movable;

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(GetRootComponent());
	SceneCapture->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SceneCapture->Mobility = EComponentMobility::Movable;
    //SceneCapture->SetTickGroup(ETickingGroup::TG_PostUpdateWork);

    PortalQuality = 1.0f;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	InitSceneCapture();
	InitTextureTarget();
    PortalMesh->OnComponentBeginOverlap.AddDynamic(this, &APortal::OverlapBegin);
    PortalMesh->OnComponentEndOverlap.AddDynamic(this, &APortal::OverlapEnd);
    if (UGameplayStatics::GetPlayerController(GetWorld(), 0) != nullptr)
        ControllerOwner = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    
    if (LinkedPortal->IsValidLowLevel()) {
        if (LinkedPortal->isAlwaysActive)
            LinkedPortal->SetRTT(PortalTexture);
        else
            LinkedPortal->ClearRTT();
    }
}

void APortal::InitSceneCapture()
{
    SceneCapture->bCaptureEveryFrame = false; // LinkedPortal->isAlwaysActive;
    SceneCapture->bCaptureOnMovement = false;
    SceneCapture->LODDistanceFactor = 3; //Force bigger LODs for faster computations
    SceneCapture->bEnableClipPlane = true;
    SceneCapture->bUseCustomProjectionMatrix = true;
    SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorHDR; // ESceneCaptureSource::SCS_SceneColorHDRNoAlpha;

    //Setup Post-Process of SceneCapture (optimization : disable Motion Blur, etc)
    FPostProcessSettings CaptureSettings;
    CaptureSettings.bOverride_AmbientOcclusionQuality = true;
    CaptureSettings.bOverride_MotionBlurAmount = true;
    CaptureSettings.bOverride_SceneFringeIntensity = true;
    CaptureSettings.bOverride_FilmGrainIntensity = true;
    CaptureSettings.bOverride_ScreenSpaceReflectionQuality = true;
    CaptureSettings.AmbientOcclusionQuality = 100.0f; //0=lowest quality..100=maximum quality
    CaptureSettings.MotionBlurAmount = 0.0f; //0 = disabled
    CaptureSettings.SceneFringeIntensity = 0.0f; //0 = disabled
    CaptureSettings.FilmGrainIntensity = 0.0f; //0 = disabled
    CaptureSettings.ScreenSpaceReflectionQuality = 0.0f; //0 = disabled
    CaptureSettings.bOverride_ScreenPercentage_DEPRECATED = true;
    CaptureSettings.ScreenPercentage_DEPRECATED = 200.0f;

    SceneCapture->PostProcessSettings = CaptureSettings;
}

void APortal::InitTextureTarget()
{
    int32 CurrentSizeX = 1920;
    int32 CurrentSizeY = 1080;
    PortalTexture = NewObject<UTextureRenderTarget2D>();
    check(PortalTexture);
    AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    PC->GetViewportSize(CurrentSizeX, CurrentSizeY);
    PortalTexture->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;
    PortalTexture->Filter = TextureFilter::TF_Bilinear;
    PortalTexture->SizeX = CurrentSizeX * PortalQuality;
    PortalTexture->SizeY = CurrentSizeY * PortalQuality;
    PortalTexture->ClearColor = FLinearColor::Black;
    PortalTexture->TargetGamma = 2.2f;
    PortalTexture->bNeedsTwoCopies = false;
    PortalTexture->AddressX = TextureAddress::TA_Clamp;
    PortalTexture->AddressY = TextureAddress::TA_Clamp;

    // Not needed since the texture is displayed on screen directly
    // in some engine versions this can even lead to crashes (notably 4.24/4.25)
    PortalTexture->bAutoGenerateMips = false;

    // This force the engine to create the render target 
    // with the parameters we defined just above
    PortalTexture->UpdateResource();
    SceneCapture->TextureTarget = PortalTexture;
    if (LinkedPortal != nullptr)
        LinkedPortal->SetRTT(PortalTexture);
}

void APortal::CheckIfPlayerShouldTeleport(AFPCharacter* Player)
{
    FVector a = Player->GetActorLocation() + Player->GetVelocity() * Player->GetWorld()->GetDeltaSeconds();
    a = a - this->GetActorLocation();
    a.Normalize();
    bool check1 = FVector::DotProduct(a, this->GetActorForwardVector()) <= 0.0f;
    FVector b = Player->GetLastMovementInputVector();
    b.Normalize();
    bool check2 = FVector::DotProduct(b, this->GetActorForwardVector()) < 0.0f;
    
    if (check1 && check2)
        TeleportPlayer(Player);
}

void APortal::TeleportPlayer(AFPCharacter* Player)
{
    if (!Player->canBeTeleported)
        return;

    SceneCapture->bCameraCutThisFrame = true;
    LinkedPortal->SceneCapture->bCameraCutThisFrame = true;
    ControllerOwner->PlayerCameraManager->SetGameCameraCutThisFrame();

    Player->DisableCameraLag();

    FVector relativeVelocity = Player->GetActorTransform().InverseTransformVectorNoScale(Player->GetVelocity());
    
    FTransform newT = Player->GetFirstPersonCameraComponent()->GetComponentTransform().GetRelativeTransform(BackFacingScene->GetComponentTransform());
    newT = newT * LinkedPortal->GetActorTransform();

    //FVector newLocation = (newT.GetLocation() - Player->GetFirstPersonCameraComponent()->GetRelativeLocation()) + (LinkedPortal->GetActorForwardVector() * 10.0f);
    FVector newLocation = (newT.GetLocation() - Player->GetSpringArmComponent()->GetRelativeLocation().Z * Player->GetActorUpVector()) + (LinkedPortal->GetActorForwardVector() * 15.0f);

    //FVector newLocation = (newT.GetLocation()) + (LinkedPortal->GetActorForwardVector() * 10.0f);
    Player->SetActorLocation(newLocation, false, nullptr, ETeleportType::TeleportPhysics);

    FRotator NewRotator = FRotator::ZeroRotator;
    NewRotator.Pitch = newT.Rotator().Pitch;
    NewRotator.Yaw = newT.Rotator().Yaw;
    NewRotator.Roll = newT.Rotator().Roll;
    Player->GetController()->SetControlRotation(NewRotator);

    FTransform newVT = FTransform::Identity;
    newVT.SetLocation(Player->GetActorLocation());
    newVT.SetRotation(Player->GetController()->GetControlRotation().Quaternion());
    Player->GetMovementComponent()->Velocity = newVT.TransformVectorNoScale(relativeVelocity);

    Player->canBeTeleported = false;
    OnPlayerCrossPortal.Broadcast();
}

void APortal::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (LinkedPortal == nullptr)
        return;

    AFPCharacter* newP = Cast<AFPCharacter>(OtherActor);
    if (newP != nullptr) 
        if (ActorsInPortal.AddUnique(newP) != -1) 
            newP->GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("PortalPawn")), true);
}

void APortal::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AFPCharacter* newP = Cast<AFPCharacter>(OtherActor);
    if (newP != nullptr) {
        ActorsInPortal.Remove(newP);
        newP->GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Pawn")), true);
    }        
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdatePortal();
}

void APortal::ResetRTT()
{
    if (LinkedPortal->IsValidLowLevelFast()) {
        if (isActive) {
            isActive = false;
            SetIsActive(true);
        }
        else
            SetRTT(LinkedPortal->PortalTexture);
    }
}

void APortal::UpdatePortal() {
    if (isActive || isAlwaysActive) {
        if (ControllerOwner != nullptr)
        {
            int32 CurrentSizeX = 1920;
            int32 CurrentSizeY = 1080;
            AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
            if (PC == nullptr)
                return;

            PC->GetViewportSize(CurrentSizeX, CurrentSizeY);
            PortalTexture->ResizeTarget(CurrentSizeX * PortalQuality, CurrentSizeY * PortalQuality);
            //AFPCharacter* Player = PC->myPlayer;
            UCameraComponent* PlayerCamera = PC->GetCurrentCamera(); // Player->GetFirstPersonCameraComponent();
            if (PlayerCamera) {
                FTransform newSceneCaptureTransform = PlayerCamera->GetComponentTransform().GetRelativeTransform(BackFacingScene->GetComponentTransform());
                LinkedPortal->SceneCapture->SetRelativeTransform(newSceneCaptureTransform);
                LinkedPortal->SceneCapture->ClipPlaneNormal = LinkedPortal->GetActorForwardVector();
                LinkedPortal->SceneCapture->ClipPlaneBase = LinkedPortal->GetActorLocation() + LinkedPortal->SceneCapture->ClipPlaneNormal * -1.0f;
                LinkedPortal->SceneCapture->CustomProjectionMatrix = ControllerOwner->GetCameraProjectionMatrix();
                //LinkedPortal->SceneCapture->CaptureScene();
            }
        }
    }
    if (!ActorsInPortal.IsEmpty()) {
        for (int i = ActorsInPortal.Num() - 1; i >= 0; i--)
            CheckIfPlayerShouldTeleport(ActorsInPortal[i]);
    }
}

bool APortal::GetIsActive() {
    return isActive;
}

void APortal::SetIsActive(bool newIsActive) {
    if (newIsActive == isActive)
        return;

    isActive = newIsActive;
    LinkedPortal->SceneCapture->bCaptureEveryFrame = isActive;
    if(isActive)
        SetRTT(LinkedPortal->PortalTexture);
    else
       ClearRTT();
}



bool APortal::IsPortalOnViewPort(AMyPlayerController* PC)
{
    int MaxX, MaxY;
    PC->GetViewportSize(MaxX, MaxY);

    if (PortalCorners.IsEmpty())
        return false;

    for (auto Corner : PortalCorners) {
        if (Corner) {
            FVector2D SL = FVector2D::ZeroVector;
            PC->ProjectWorldLocationToScreen(Corner->GetComponentLocation(), SL, false);
            if (SL.X > 0 && SL.X < MaxX && SL.Y > 0 && SL.Y < MaxY)
                return true;
        }
    }

    return false;
}

bool APortal::IsPlayerLookingAtPortal(AMyPlayerController* PC) {

    FRotator cameraRot = PC->GetCurrentCamera()->GetComponentRotation();
    FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(PC->GetCurrentCamera()->GetComponentLocation(), this->GetActorLocation());
    float delta = 130.0f;

    return UKismetMathLibrary::InRange_FloatFloat(cameraRot.Yaw, lookAtRot.Yaw - delta, lookAtRot.Yaw + delta);
        //|| UKismetMathLibrary::InRange_FloatFloat(cameraRot.Pitch, lookAtRot.Pitch - delta, lookAtRot.Pitch + delta)
        //|| UKismetMathLibrary::InRange_FloatFloat(cameraRot.Roll, lookAtRot.Roll - delta, lookAtRot.Roll + delta);
}

void APortal::ClearRTT_Implementation()
{

}

void APortal::SetRTT_Implementation(UTextureRenderTarget2D* RenderTexture)
{

}
