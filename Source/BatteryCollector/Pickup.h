// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // asseccor: return the mesh for the pickup
    FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

    // Return whether or not the pickup is active
    UFUNCTION(BlueprintPure, Category = "Pickup")
    bool IsActive();
    
    // allows other classes safely change whether pickup is active
    UFUNCTION(BlueprintCallable, Category = "Pickup")
    void SetActive(bool NewPickupState);
    
    // function to call when the pickup is collected
    // - make this a blueprint native event
    UFUNCTION(BlueprintNativeEvent)
    void WasCollected();
  
    virtual void WasCollected_Implementation();

    
protected:
    // true when the pickup can be used, false when pickup is deactivated
    bool bIsActive;
    
private:
    // static mesh to represent the pickup in the level
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
              meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* PickupMesh;
	
};
