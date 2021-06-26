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
	RootComponent = CapsuleComponent;

	ShipPivotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ship Pivot Point"));
	ShipPivotPoint->SetupAttachment(RootComponent);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	ShipMesh->SetupAttachment(ShipPivotPoint);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(ShipMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::InitPawn(bool IsColorBlue) 
{
	SetIsBlue(IsColorBlue);
}

void APawnBase::Fire() 
{
	if (ProjectileClass != nullptr) {
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
		SpawnedProjectile->InitProjectile(IsBlue, IsBlue ? BlueMaterial : RedMaterial);
		SpawnedProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction() 
{
	UE_LOG(LogTemp, Warning, TEXT("Called PawnBase::HandleDestruction()"));	
}

void APawnBase::SetIsBlue(bool IsNewColorBlue) 
{
	IsBlue = IsNewColorBlue;
	if (IsBlue) 
    {
        ShipMesh->SetMaterial(1, BlueMaterial);
    }
    else
    {
        ShipMesh->SetMaterial(1, RedMaterial);
    }
}

bool APawnBase::GetIsBlue() 
{
	return IsBlue;
}