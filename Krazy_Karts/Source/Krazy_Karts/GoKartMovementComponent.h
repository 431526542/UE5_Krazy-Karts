// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"


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

	bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(Steeringthrow) <= 1;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZY_KARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SimulateMove(const FGoKartMove& Move);
	

	FVector GetVelocity() { return Velocity; }
	void SetVelocity(FVector Val) { Velocity = Val; }
	void SetThrottle(float Val) { Throttle = Val; }
	void SetSteeringthrow(float Val) { Steeringthrow = -Val; }
	FGoKartMove GetLastMove() { return LastMove; }
private:
	FGoKartMove CreateMove(float DeltaTime);
	FVector GetAirResistance();
	FVector GetRolllingResistance();
	void ApplyRotaion(float DeltaTime, float SteeringThrow);
	void UpdateLocationFromVelocity(float DeltaTime);

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

	FVector Velocity;
	float Throttle;
	float Steeringthrow;
	FGoKartMove LastMove;
};
