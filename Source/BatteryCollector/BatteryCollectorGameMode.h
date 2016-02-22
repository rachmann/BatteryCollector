// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"


//enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState
{
    EPlaying,
    EGameOver,
    EWon,
    EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
    GENERATED_BODY()
    

public:
	ABatteryCollectorGameMode();
    
    virtual void Tick(float DeltaTime) override;
    
    // returns power needed to win - needed for the HUD
    UFUNCTION(BlueprintPure, Category = "Power")
    float GetPowerToWin() const;
    
    virtual void BeginPlay() override;
    
    // Returns the current playing state
    UFUNCTION(Blueprintpure, Category = "Power")
    EBatteryPlayState GetCurrentState() const;
    
    // Sets a new playing state
    void SetCurrentState(EBatteryPlayState NewState);
    
protected:
    // Game Mode - this file - sets the rules of the game...
    //
    // The rate at which the character loses power
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float DecayRate;
    
    // The power needed to win the game
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float PowerToWin;
    
    // The widget class to use for the HUD screen
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    TSubclassOf<class UUserWidget> HUDWidgetClass;
    
    // The Actual Instance of the HUD
    UPROPERTY()
    class UUserWidget* CurrentWidget;
    
private:
    
    // keeps track of current play state
    EBatteryPlayState CurrentState;
    
    // Collection of spawn volumes
    TArray<class ASpawnVolume*> SpawnVolumeActors;
    
};



