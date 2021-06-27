#include "TwoSides/Components/HealthComponent.h"
#include "TwoSides/GameModes/TwoSidesGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// Grab a reference to the GameMode
	GameModeRef = Cast<ATwoSidesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UHealthComponent::TakeDamage: No GameModeRef found!"));
	}
	// Initialize starting HP
	Health = DefaultHealth;
	// Bind our Take Damage function
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) 
{
	UE_LOG(LogTemp, Warning, TEXT("We Got Hit, Damage: %f, Before Health: %f, After Health: %f"), Damage, Health, Health - Damage);
	if (Damage == 0 || Health <= 0) 
	{
		return;
	}
	Health -= Damage;
	// Handle this actor getting killed by notifying the game mode
	if (Health <= 0)
	{
		if (GameModeRef) 
		{
			GameModeRef->ActorDied(GetOwner());
		}
	} 
	// If this actor was not killed, notify Game Mode to update HP (if player)
	else
	{
		GameModeRef->ActorDamaged(GetOwner());
	}
}

void UHealthComponent::SetDefaultHealth(float NewHealth) 
{
	DefaultHealth = NewHealth;
	Health = DefaultHealth;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return DefaultHealth;
}