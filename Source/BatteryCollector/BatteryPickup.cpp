// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"




// Set default values
ABatteryPickup::ABatteryPickup()
{
    GetMesh()->SetSimulatePhysics(true);
    
    // the base power level of the battery
    BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
    // call the base pickup behaviour...
    Super::WasCollected_Implementation();
    // destroy the battery
    Destroy();
    
}

// Report the power level of the battery
float ABatteryPickup::GetPower()
{
    return BatteryPower;
}