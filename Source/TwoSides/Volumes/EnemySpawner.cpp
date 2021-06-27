#include "TwoSides/Volumes/EnemySpawner.h"
#include "TwoSides/GameModes/TwoSidesGameMode.h"
#include "TwoSides/Pawns/PawnEnemyShip.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AEnemySpawner::AEnemySpawner() 
{
    
}

void AEnemySpawner::BeginPlay() 
{
    Super::BeginPlay();
	GameModeRef = Cast<ATwoSidesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameModeRef == nullptr) 
    {
        UE_LOG(LogTemp, Error, TEXT("AEnemySpawner: Cannot find GameMode!"));
    }
    GetWorldTimerManager().SetTimer(SpawnEnemyTimer, this, &AEnemySpawner::SpawnEnemy, SpawnEnemyTime, true);
}

void AEnemySpawner::SpawnEnemy() 
{
    if (GameModeRef == nullptr) return;
    // Make sure we haven't hit our enemy spawn limit
    if (GameModeRef->GetEnemyCount() < GameModeRef->GetMaxEnemies())
    {
        // Spawn a boss every [BossSpawnFrequency] kills
        if ((GameModeRef->GetEnemiesKilled() % BossSpawnFrequency) == 0 && GameModeRef->GetEnemiesKilled() != GameModeRef->GetCurrentEnemiesKilled()) 
        {
            SpawnEnemyTwo();
        }
        // Spawn a regular enemy after a random delay
        else
        {
            float Delay = UKismetMathLibrary::RandomFloatInRange(EnemyOneDelayMinTime, EnemyOneDelayMaxTime);
            GetWorldTimerManager().SetTimer(EnemyOneDelayTimer, this, &AEnemySpawner::SpawnEnemyOne, Delay, false);
        }
    }
}

void AEnemySpawner::SpawnEnemyOne() 
{
    UE_LOG(LogTemp, Warning, TEXT("Spawn Enemy One"));
    if (EnemyOneClass == nullptr) return; 
    GameModeRef->UpdateEnemyCount(GameModeRef->GetEnemyCount() + 1);
    FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), GetComponentsBoundingBox().GetExtent());
    RandomLocation.Z = 100;
    GetWorld()->SpawnActor<APawnEnemyShip>(EnemyOneClass, RandomLocation, FRotator::ZeroRotator);
}

void AEnemySpawner::SpawnEnemyTwo() 
{
    UE_LOG(LogTemp, Warning, TEXT("Spawn Enemy Two"));
    if (EnemyTwoClass == nullptr) return; 
    GameModeRef->SetCurrentEnemiesKilled(GameModeRef->GetEnemiesKilled());
    GetWorld()->SpawnActor<APawnEnemyShip>(EnemyTwoClass, GetActorLocation(), FRotator::ZeroRotator);
}
