#include "TwoSides/Components/HealthComponent.h"
#include "TwoSides/GameModes/TwoSidesGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	// Bind OnTakeAnyDamage -> TakeDamage()
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage == 0 || Health <= 0) 
	{
		return;
	}
	Health -= Damage;
	if (Health <= 0)
	{
		if (GameModeRef) 
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("UHealthComponent::TakeDamage: No GameModeRef found!"));
		}
	} 
}