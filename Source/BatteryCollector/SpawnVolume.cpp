// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // create the box component to represent the spawn volume
    WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSPawn"));
    RootComponent = WhereToSpawn;
    
    // Set spawn delay range
    SpawnDelayRangeLow = 1.0f;
    SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
    // could break out low and high values to be returned from a function
    SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
    
    GetWorldTimerManager().SetTimer(SpawnTimer,this, &ASpawnVolume::SpawnPickup, SpawnDelay,false);

}

// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
    FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
    
    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnPickup()
{
    //  If we have set something to spawn:
    if(WhatToSpawn != NULL)
    {
    //      Check for a valid world:
        UWorld* const World = GetWorld();
        if(World)
        {
            // Set the spawn parameters
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            
            // Get a random location to spawn at
            FVector SpawnLocation = GetRandomPointInVolume();
            
            // Get a random rotation for the spawned item
            FRotator SpawnRotation;
            SpawnRotation.Yaw = FMath::FRand() * 360.0f;
            SpawnRotation.Pitch = FMath::FRand() * 360.0f;
            SpawnRotation.Roll = FMath::FRand() * 360.0f;
            
            // Spawn the pickup
            APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
            
            SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
            
            GetWorldTimerManager().SetTimer(SpawnTimer,this, &ASpawnVolume::SpawnPickup, SpawnDelay,false);
            
        }
    }
}