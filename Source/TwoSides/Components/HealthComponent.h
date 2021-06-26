
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWOSIDES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.f;
	UPROPERTY(VisibleAnywhere)	
	float Health = 0.f;

	class ATwoSidesGameMode* GameModeRef;
		
};
