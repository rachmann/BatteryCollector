// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // returns the WhereTOSpawn subobject
    FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }
    
    // Find a random point within the BoxComponent
    UFUNCTION(BlueprintPure, Category = "Spawning")
    FVector GetRandomPointInVolume();

protected:
    // The pickup to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class APickup> WhatToSpawn;
    
    // timer handle
    FTimerHandle SpawnTimer;
    
    // Minimum spawn delay
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnDelayRangeLow;

    // Maximum spawn delay
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnDelayRangeHigh;
    
private:
    // Box component to specify where the pickups should be spawned
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning",
              meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* WhereToSpawn;

    // Hanlde spawning a new pickup
    void SpawnPickup();
    
    // Set *this* rule in code and not any child class like a blueprint
    // so this is private so that blueprint has no access
    //   (you'd also need to add a property accessor
    //
    // The current spawn delay
    float SpawnDelay;
    
    
};
