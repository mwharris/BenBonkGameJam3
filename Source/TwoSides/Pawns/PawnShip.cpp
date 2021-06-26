#include "TwoSides/Pawns/PawnShip.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnShip::APawnShip() 
{

}

void APawnShip::BeginPlay() 
{
    Super::BeginPlay();
}

void APawnShip::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &APawnShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnShip::Fire);
}

void APawnShip::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    FVector Movement = FVector(VerticalMovement, HorizontalMovement, 0) * DeltaTime;
    FVector NewLocation = GetActorLocation() + Movement;
    SetActorLocation(NewLocation, true);
}

void APawnShip::MoveUp(float AxisValue) 
{
    VerticalMovement = AxisValue * MovementSpeed;
}

void APawnShip::MoveRight(float AxisValue) 
{
    HorizontalMovement = AxisValue * MovementSpeed;
}

void APawnShip::HandleDestruction() 
{
    Super::HandleDestruction();
}