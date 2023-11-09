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

	UFUNCTION(BlueprintCallable)
	void OnRep_ReplicatedVar();

	// you have to use this for replicated variables, just copy and paste from another project. This is from the Actor class, this does the replication for us
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

};
