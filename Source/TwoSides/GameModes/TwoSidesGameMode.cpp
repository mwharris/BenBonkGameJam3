#include "TwoSides/GameModes/TwoSidesGameMode.h"
#include "TwoSides/Pawns/PawnEnemyShip.h"
#include "TwoSides/Pawns/PawnShip.h"
#include "Kismet/GameplayStatics.h"

void ATwoSidesGameMode::BeginPlay() 
{
    PlayerShip = Cast<APawnShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerShip == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("GameMode: Can't find player ship!"));
    }
}

void ATwoSidesGameMode::ActorDied(AActor* DeadActor) 
{
    if (Cast<APawnShip>(DeadActor))
    {
        // Player died...
    }
    else if (APawnEnemyShip* DeadEnemy = Cast<APawnEnemyShip>(DeadActor))
    {
        EnemiesKilled++;
        DeadEnemy->HandleDestruction();
    }
}

void ATwoSidesGameMode::UpdateEnemyCount(int32 Val) 
{
    EnemyCount = Val;
}

int32 ATwoSidesGameMode::GetEnemyCount() 
{
    return EnemyCount;
}

int32 ATwoSidesGameMode::GetMaxEnemies() 
{
    return MaxEnemies;
}

int32 ATwoSidesGameMode::GetEnemiesKilled() 
{
    return EnemiesKilled;
}

int32 ATwoSidesGameMode::GetCurrentEnemiesKilled() 
{
    return CurrentEnemiesKilled;
}

void ATwoSidesGameMode::SetCurrentEnemiesKilled(float Val) 
{
    CurrentEnemiesKilled = Val;
}

int32 ATwoSidesGameMode::GetScore() 
{
    return Score;
}
