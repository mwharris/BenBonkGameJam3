#include "TwoSides/Pawns/PawnEnemyShip.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TwoSides/Actors/ProjectileBase.h"
#include "TwoSides/GameModes/TwoSidesGameMode.h"
#include "TwoSides/Pawns/PawnShip.h"

APawnEnemyShip::APawnEnemyShip() 
{
	CapsuleComponent->OnComponentHit.AddDynamic(this, &APawnEnemyShip::OnHit);
}

void APawnEnemyShip::BeginPlay() 
{
    Super::BeginPlay();
    // Grab a reference to the game mode
	GameModeRef = Cast<ATwoSidesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameModeRef == nullptr) 
    {
        UE_LOG(LogTemp, Error, TEXT("APawnEnemyShip: Cannot find GameMode!"));
    }
    // Grab a reference to the player
    PlayerShip = Cast<APawnShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerShip == nullptr) 
    {
	    UE_LOG(LogTemp, Error, TEXT("APawnEnemyShip couldn't find Player Ship!"));	
    }
    // Pick red or blue for this enemy
    SetIsBlue(UKismetMathLibrary::RandomBool(), false);
    // Set some default values
    MoveDirectionFlag = UKismetMathLibrary::RandomBool();
    MovementSpeed = UKismetMathLibrary::RandomFloatInRange(MinSpeed, MaxSpeed);
    SpawnLocation = GetActorLocation();
}

void APawnEnemyShip::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (!MoveEnabled || GameModeRef->IsGameOver() || PlayerShip == nullptr) return;
    // Move back and forth according to MovementValue
    float MovementValue = MovementSpeed * (MoveDirectionFlag ? 1 : -2) * DeltaTime;
    FVector NewLocation = GetActorLocation() + FVector(0, MovementValue, 0);
    SetActorLocation(NewLocation, true);
    // Shoot at the player periodically when in range
    float XDistance = PlayerShip->GetActorLocation().X - GetActorLocation().X;
    if (!Shooting && XDistance <= FireDistance) 
    {
        Shooting = true;
        float ShootTime = UKismetMathLibrary::RandomFloatInRange(FireRateMin, FireRateMax);
        GetWorldTimerManager().SetTimer(ShootTimer, this, &APawnEnemyShip::ShootPlayer, ShootTime , false);
    }
}

void APawnEnemyShip::ShootPlayer() 
{
    Shooting = false;
    Fire();
}

void APawnEnemyShip::Fire() 
{
    if (ProjectileClass == nullptr) return;
    else if (PlayerShip == nullptr) Super::Fire();
    else
    {
	    FVector Location = ProjectileSpawnPoint->GetComponentLocation();
        // Shoot towards the player
        FVector PlayerDirection = PlayerShip->GetActorLocation() - GetActorLocation();
        FRotator Rotation = PlayerDirection.Rotation();
        // Spawn the projectile
        AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
        SpawnedProjectile->InitProjectile(IsBlue, IsBlue ? BlueMaterial : RedMaterial);
        SpawnedProjectile->SetOwner(this);
    }
}

void APawnEnemyShip::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
    // Ignore collisions from projectiles and other enemies
    if (AProjectileBase* Projectile = Cast<AProjectileBase>(OtherActor)) return;
    if (APawnEnemyShip* EnemyShip = Cast<APawnEnemyShip>(OtherActor)) return;
    // Crashed into the player - apply damage if different color
    if (OtherActor == PlayerShip) 
    {
        if ((PlayerShip->GetIsBlue() && !GetIsBlue()) || (!PlayerShip->GetIsBlue() && GetIsBlue()))
        {
            UGameplayStatics::ApplyDamage(PlayerShip, 50.f, GetInstigatorController(), this, DamageType);
        }
        GameModeRef->ActorDied(this);
    }
    // Otherwise, reverse our direction
    else
    {
        MoveDirectionFlag = !MoveDirectionFlag;
    }
}

void APawnEnemyShip::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

int32 APawnEnemyShip::GetScoreValue() const
{
    return ScoreValue;
}

bool APawnEnemyShip::IsBoss() 
{
    return Boss;
}