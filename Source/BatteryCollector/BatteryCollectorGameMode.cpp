// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SpawnVolume.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    
    // base decay rate
    DecayRate = 0.01f;
}

void  ABatteryCollectorGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // find all spawn volum actors
    TArray<AActor *> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
    
    for(auto Actor : FoundActors)
    {
        ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
        if(SpawnVolumeActor)
        {
            SpawnVolumeActors.AddUnique(SpawnVolumeActor);
        }
    }
    
    SetCurrentState(EBatteryPlayState::EPlaying);
    
    // Set the score to beat to win
    ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    if(MyCharacter)
    {
        PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
    }
    
    if(HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
    

}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // check that it's a batter collector character
    ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    if(MyCharacter)
    {
        // if power is greater than needed to win, set the game's state to Won
        if(MyCharacter->GetCurrentPower() > PowerToWin)
        {
            SetCurrentState(EBatteryPlayState::EWon);
        }
        // if the character's poer is positive
        else if(MyCharacter->GetCurrentPower()>0)
        {
            // decrease the character's power
            MyCharacter->UpdatePower(-DeltaTime*DecayRate*(MyCharacter->GetInitialPower()));
        }
        else {
            SetCurrentState(EBatteryPlayState::EGameOver);
        }
    }
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
    return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
    return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
    // Set Current State
    CurrentState = NewState;
    // Handle the new current state
    HandleNewState(CurrentState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{

    
    switch (NewState) {
        case EBatteryPlayState::EPlaying :
            
            // If the game is playing
            //
            // spawn volume active
            for (ASpawnVolume* Volume : SpawnVolumeActors) {
                Volume->SetSpawningActive(true);
            }
            
            break;
        case EBatteryPlayState::EWon :
            
            // if we won the game
            //
            // spawn volume inactive
            for (ASpawnVolume* Volume : SpawnVolumeActors) {
                Volume->SetSpawningActive(false);
            }
            
            
            break;
        case EBatteryPlayState::EGameOver :
        {
            // If we lost
            //
            // spawn volume inactive
            // block player input
            // ragdoll the character
            for (ASpawnVolume* Volume : SpawnVolumeActors) {
                Volume->SetSpawningActive(false);
            }
            
            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            if(PlayerController)
            {
                PlayerController->SetCinematicMode(true, false, false, true, true);
                
                UE_LOG(LogClass, Log, TEXT("You have set Cinematic Mode"));

            }
            else
            {
                UE_LOG(LogClass, Log, TEXT("Player Controller was invalid!!"));
            }

            // now ragdoll the character
            ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
            if(MyCharacter)
            {
                MyCharacter->GetMesh()->SetSimulatePhysics(true);
                MyCharacter->GetMovementComponent()->MovementState.bCanJump=false;
                
                UE_LOG(LogClass, Log, TEXT("ACharacter jump turned off and Set Simulate Physics on"));
            }else
            {
                UE_LOG(LogClass, Log, TEXT("ACharacter was invalid!! (EGameOver State in HandleNewState"));

            }
        }
            
            break;
            
        default :

            // unknown state - incase some code forgets to call
            //
            // use to help debug
            
            break;
    }
}