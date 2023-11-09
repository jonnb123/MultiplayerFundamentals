// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.f;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicates(true);
	SetReplicateMovement(true);
}


// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (HasAuthority())
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Server"));
	// }
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Client"));
	// }

}

// every time a client receives replicated information on ReplicatedVar, this function will be called on the client.
void AMyBox::OnRep_ReplicatedVar()
{
	if (HasAuthority())
	{
		FVector NewLocation = GetActorLocation() + FVector(0,0,200.f);
		SetActorLocation(NewLocation);
		GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"));
	}
	else
	{
		// GPlayInEditorID is just the client number
		GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Yellow, 
		FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
	}
}

// this function replicates the variable
void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// this checks that replicatedvar of the mybox class is actually replicated. 
	// this will only work if the actor itself is replicated
	DOREPLIFETIME(AMyBox, ReplicatedVar);


}

