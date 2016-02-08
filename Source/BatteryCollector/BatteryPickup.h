// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ABatteryPickup();
	
    // override WasCollected function
    // - use Implementation because it's a Blueprint Native Event
    void WasCollected_Implementation() override;
    
    // the public way to access the battery power level
    float GetPower();
    
protected:
    
    // set the amount of poswer the battery gives to the character
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float BatteryPower;
	
};
