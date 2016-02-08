// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();
    
    virtual void Tick(float DeltaTime) override;
    
protected:
    // Game Mode - this file - sets the rules of the game...
    //
    // the rate at which the character loses power
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
    float DecayRate;
};



