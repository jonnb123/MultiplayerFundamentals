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

	if (HasAuthority())
	{
		// GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVar, 2.0f, false);
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::MulticastRPCExplode, 2.0f, false);

	}
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
		FVector NewLocation = GetActorLocation() + FVector(0, 0, 200.f);
		SetActorLocation(NewLocation);
		// GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"));
	}
	else
	{
		// GPlayInEditorID is just the client number
		// GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Yellow, FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
	}
}

void AMyBox::MulticastRPCExplode_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Red, TEXT("Server: MulticastRPCExplode_Implementation"));
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::MulticastRPCExplode, 2.0f, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Green, TEXT("Client: MulticastRPCExplode_Implementation"));
	}
}

// this function replicates the variable
void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// this checks that replicatedvar of the mybox class is actually replicated.
	// this will only work if the actor itself is replicated
	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

void AMyBox::DecreaseReplicatedVar()
{
	if (HasAuthority())
	{
		ReplicatedVar -= 1.0f; // here we are modifying the RepNotify replicated variable
		OnRep_ReplicatedVar(); // this is required to work on the server
		if (ReplicatedVar > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVar, 2.0f, false);
		}
	}
}
