// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBox.generated.h"

UCLASS()
class MULTIPLAYERCOURSE_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// OnRep_ReplicatedVar is the function below
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedVar, BlueprintReadWrite)
	float ReplicatedVar;

	// called when ReplicatedVar changes on the client automatically, needs to be called manually for the server
	UFUNCTION(BlueprintCallable)
	void OnRep_ReplicatedVar();

	// multicast rpcs are called from the server, then executed on the clients and server
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MulticastRPCExplode();

	// you have to use this for replicated variables, just copy and paste from another project. This is from the Actor class, this does the replication for us
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void DecreaseReplicatedVar();
	FTimerHandle TestTimer;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

};
