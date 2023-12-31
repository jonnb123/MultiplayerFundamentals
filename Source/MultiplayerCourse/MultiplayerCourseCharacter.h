// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MultiplayerCourseCharacter.generated.h"


UCLASS(config=Game)
class AMultiplayerCourseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AMultiplayerCourseCharacter();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// USE RPCS sparingly, use RepNotify where possible
	// If you call an RPC often make it Unreliable, i.e. on Tick
	// See MyBox.h for Multicast RPC
	// DON'T DO THE FOLLOWING WITH RPCs, i.e.:
	// Client RPC called on client
	// client RPC called on server on server-owned/unowned actor
	// Server RPC called on server
	// Multicast RPC called on Client
	
	// server rpcs are called on the client, executed on server
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerRPCFunction(int MyArg);

	// client rpcs are called on the server, executed on a specific client
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientRPCFunction();

	UPROPERTY(EditAnywhere)
	UParticleSystem* ClientParticles;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SphereMesh;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();


	
};

