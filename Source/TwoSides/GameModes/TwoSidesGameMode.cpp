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
        DeadEnemy->HandleDestruction();
    }
}

void ATwoSidesGameMode::UpdateEnemyCount() 
{
    
}
