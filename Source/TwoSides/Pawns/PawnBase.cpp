#include "TwoSides/Pawns/PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TwoSides/Actors/ProjectileBase.h"
#include "TwoSides/Components/HealthComponent.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);
    CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
    CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
    CapsuleComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	RootComponent = CapsuleComponent;

	ShipPivotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ship Pivot Point"));
	ShipPivotPoint->SetupAttachment(RootComponent);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	ShipMesh->SetCollisionResponseToAllChannels(ECR_Block);
    ShipMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
    ShipMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
    ShipMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	ShipMesh->SetupAttachment(ShipPivotPoint);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(ShipMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::Fire() 
{
	if (ProjectileClass == nullptr) return;
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
	SpawnedProjectile->InitProjectile(IsBlue, IsBlue ? BlueMaterial : RedMaterial);
	SpawnedProjectile->SetOwner(this);
}

void APawnBase::HandleDestruction() 
{
	// Play particle effect
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), FRotator::ZeroRotator);
	// Play camera shake effect
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(DeathCameraShake);
	// Play an explosion sound
    UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);
}

void APawnBase::SetIsBlue(bool IsNewColorBlue, bool IsPlayer) 
{
	IsBlue = IsNewColorBlue;
	if (IsBlue) 
    {
        ShipMesh->SetMaterial(IsPlayer ? 1 : 3, BlueMaterial);
    }
    else
    {
        ShipMesh->SetMaterial(IsPlayer ? 1 : 3, RedMaterial);
    }
}

void APawnBase::PlayHitSound() 
{
    UGameplayStatics::PlaySound2D(GetWorld(), PlayerHitSound);
}

bool APawnBase::GetIsBlue() 
{
	return IsBlue;
}

int32 APawnBase::GetHealth() 
{
	return HealthComp->GetHealth();
}

int32 APawnBase::GetMaxHealth() 
{
	return HealthComp->GetMaxHealth();
}