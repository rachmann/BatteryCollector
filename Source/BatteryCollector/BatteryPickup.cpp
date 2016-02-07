// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"




// Set default values
ABatteryPickup::ABatteryPickup()
{
    GetMesh()->SetSimulatePhysics(true);
    
}

void ABatteryPickup::WasCollected_Implementation()
{
    // call the base pickup behaviour...
    Super::WasCollected_Implementation();
    // destroy the battery
    Destroy();
    
}