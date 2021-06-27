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
    if (GameModeRef == nullptr || GameModeRef->IsGameOver()) return;
    if (GameModeRef->GetBossesKilled() % RampUpBossFrequency == 0 && GameModeRef->GetBossesKilled() > 0) 
    {
        // Increase spawn rate
        GameModeRef->SetBossesKilled(0);
        if (UKismetMathLibrary::RandomBool() && EnemyOneDelayMinTime >= 0.1f)
        {
            EnemyOneDelayMinTime -= 0.1;
        }
        else
        {
            EnemyOneDelayMaxTime -= 0.1;
        }
        UE_LOG(LogTemp, Warning, TEXT("Ramping up, Min: %f, Max: %f"), EnemyOneDelayMinTime, EnemyOneDelayMaxTime);
    }
    // Make sure we haven't hit our enemy spawn limit
    if (GameModeRef->GetEnemyCount() < GameModeRef->GetMaxEnemies())
    {
        // Spawn a boss every [BossSpawnFrequency] kills
        int32 EnemiesKilledDifference = GameModeRef->GetEnemiesKilled() - GameModeRef->GetCurrentEnemiesKilled();
        if (EnemiesKilledDifference >= BossSpawnFrequency && GameModeRef->GetEnemiesKilled() != GameModeRef->GetCurrentEnemiesKilled()) 
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
    if (EnemyOneClass == nullptr || GameModeRef->IsGameOver()) return; 
    GameModeRef->UpdateEnemyCount(GameModeRef->GetEnemyCount() + 1);
    // Pick a random location in the spawner to spawn
    FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), GetComponentsBoundingBox().GetExtent());
    RandomLocation.Z = 100;
    // Spawn the enemy
    GetWorld()->SpawnActor<APawnEnemyShip>(EnemyOneClass, RandomLocation, FRotator::ZeroRotator);
}

void AEnemySpawner::SpawnEnemyTwo() 
{
    if (EnemyTwoClass == nullptr || GameModeRef->IsGameOver()) return; 
    GameModeRef->SetCurrentEnemiesKilled(GameModeRef->GetEnemiesKilled());
    APawnEnemyShip* NewBoss = GetWorld()->SpawnActor<APawnEnemyShip>(EnemyTwoClass, GetActorLocation(), FRotator::ZeroRotator);
    NewBoss->SetIsBoss(true);
}
