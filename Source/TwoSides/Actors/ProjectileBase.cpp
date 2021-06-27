#include "TwoSides/Actors/ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TwoSides/Pawns/PawnShip.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SelfDestructTimer, this, &AProjectileBase::HandleDestruction, DestructTime, false);
	// Grab a reference to the player ship
    PlayerShip = Cast<APawnShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerShip == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("AProjectileBase: Can't find player ship!"));
    }
}

void AProjectileBase::InitProjectile(bool IsColorBlue, UMaterialInstance* Material) 
{
	IsBlue = IsColorBlue;
	ProjectileMesh->SetMaterial(0, Material);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) return;
	if (OtherActor != nullptr && OtherActor != this && OtherActor != MyOwner) {
		// Don't apply damage to the player unless we're different colors
		if (OtherActor == PlayerShip) 
		{
			if ((PlayerShip->GetIsBlue() && !IsBlue) || (!PlayerShip->GetIsBlue() && IsBlue))
			{
				UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			}
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		}
		// Destroy ourselves
		HandleDestruction();
	}
}

void AProjectileBase::HandleDestruction() 
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

bool AProjectileBase::GetIsBlue() 
{
	return IsBlue;
}