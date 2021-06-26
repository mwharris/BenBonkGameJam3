#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwoSidesGameMode.generated.h"

UCLASS()
class TWOSIDES_API ATwoSidesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);
	void UpdateEnemyCount();

protected:
	virtual void BeginPlay() override;

private:
	class APawnShip* PlayerShip;

};
