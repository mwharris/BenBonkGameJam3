#include "TwoSides/GameModes/TwoSidesGameMode.h"
#include "TwoSides/Pawns/PawnEnemyShip.h"
#include "TwoSides/Pawns/PawnShip.h"
#include "Kismet/GameplayStatics.h"

void ATwoSidesGameMode::BeginPlay() 
{
    Super::BeginPlay();
    PlayerShip = Cast<APawnShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerShip == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("GameMode: Can't find player ship!"));
    }
    NotifyUIUpdateScore();
}

void ATwoSidesGameMode::ActorDied(AActor* DeadActor) 
{
    if (PlayerShip == DeadActor)
    {
        GameOver = true;
        NotifyUIUpdateHealth();
        NotifyUIGameOver();
        PlayerShip->HandleDestruction();
    }
    else if (APawnEnemyShip* DeadEnemy = Cast<APawnEnemyShip>(DeadActor))
    {
        if (DeadEnemy->IsBoss()) 
        {
            BossesKilled++;
            UE_LOG(LogTemp, Warning, TEXT("Boss killed!"));
        }
        EnemiesKilled++;
        EnemyCount--;
        // Update our Scores here and in the UI
        Score += DeadEnemy->GetScoreValue();
        if (Score > TopScore) { TopScore = Score; }
        NotifyUIUpdateScore();
        // Destroy the dead enemy
        DeadEnemy->HandleDestruction();
    }
}

void ATwoSidesGameMode::ActorDamaged(AActor* DamagedActor) 
{
    if (DamagedActor == PlayerShip) 
    {
        GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(PlayerShip->DamagedCameraShake);
        NotifyUIUpdateHealth();
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

int32 ATwoSidesGameMode::GetBossesKilled() 
{
    return BossesKilled;
}

void ATwoSidesGameMode::SetBossesKilled(int32 Val) 
{
    BossesKilled = Val;
}

int32 ATwoSidesGameMode::GetCurrentEnemiesKilled() 
{
    return CurrentEnemiesKilled;
}

bool ATwoSidesGameMode::IsGameOver() const
{
    return GameOver;
}

void ATwoSidesGameMode::SetCurrentEnemiesKilled(float Val) 
{
    CurrentEnemiesKilled = Val;
}

int32 ATwoSidesGameMode::GetScore() const
{
    return Score;
}
