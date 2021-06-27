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
	Health = DefaultHealth;
	GameModeRef = Cast<ATwoSidesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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
	if (Health <= 0)
	{
		if (GameModeRef) 
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode is here!"));
			GameModeRef->ActorDied(GetOwner());
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("UHealthComponent::TakeDamage: No GameModeRef found!"));
		}
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