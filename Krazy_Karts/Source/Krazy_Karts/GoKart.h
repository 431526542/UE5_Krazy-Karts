// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float Steeringthrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;
};

USTRUCT()
struct FGoKartState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FVector Velocity;

	UPROPERTY()
	FGoKartMove LastMove;
};

UCLASS()
class KRAZY_KARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendMove(FGoKartMove Move);

	void MoveRight(float Value);
private:
	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
	FGoKartState ServerState;

	FVector Velocity;

	UFUNCTION()
	void OnRep_ServerState();

	float Throttle;
	float Steeringthrow;

	TArray<FGoKartMove> UnacknowledgedMoves;

private:
	void SimulateMove(const FGoKartMove& Move);
	FGoKartMove CreateMove(float DeltaTime);
	void ClearAcknowledgeMoves(FGoKartMove LastMove);
	void ApplyRotaion(float DeltaTime, float SteeringThrow);
	void UpdateLocationFromVelocity(float DeltaTime);
	FVector GetAirResistance();
	FVector GetRolllingResistance();

private:
	// The mass of the car (kg).
	UPROPERTY(EditAnywhere)
	float Mass = 1000.f;

	//The force applied to the car when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000.f;

	//Minimum radius of the car turning circle at full llock (m).
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10.f;

	//Higher means more drag (kg/s)
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16.f;

	//Higher means more rolling resistance (kg/s)
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015;
};
