#include "TwoSides/Pawns/PawnEnemyShip.h"
#include "Kismet/KismetMathLibrary.h"

APawnEnemyShip::APawnEnemyShip() 
{
    
}

void APawnEnemyShip::BeginPlay() 
{
    Super::BeginPlay();
    MoveDirectionFlag = UKismetMathLibrary::RandomBool();
    MovementSpeed = UKismetMathLibrary::RandomFloatInRange(MinSpeed, MaxSpeed);
    SpawnLocation = GetActorLocation();
}

void APawnEnemyShip::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    float MovementValue = MovementSpeed * (MoveDirectionFlag ? 1 : -2) * DeltaTime;
    FVector NewLocation = GetActorLocation() + FVector(0, MovementValue, 0);
    SetActorLocation(NewLocation);
}

void APawnEnemyShip::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}
