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
	void UpdateEnemyCount(int32 Val);

	void SetCurrentEnemiesKilled(float Val);
	
	int32 GetEnemyCount(); 
	int32 GetMaxEnemies(); 
	int32 GetEnemiesKilled(); 
	int32 GetCurrentEnemiesKilled();
	int32 GetScore(); 

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 MaxEnemies; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 EnemyCount; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 TopScore;

	class APawnShip* PlayerShip;
	float EnemiesKilled = 0.f;
	float CurrentEnemiesKilled = 0.f;

};
