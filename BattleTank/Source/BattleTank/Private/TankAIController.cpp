// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing: %s"), *(ControlledTank->GetName()));
	}

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not detecting the player tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller is detecting: %s"), *(PlayerTank->GetName()));
	}
}

//Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO Move towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//Fire if ready
	}

	return;
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr;  }
	return Cast<ATank>(GetPawn());
}