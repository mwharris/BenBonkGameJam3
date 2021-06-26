#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TWOSIDES_API AEnemySpawner : public ATriggerBox
{
	GENERATED_BODY()

public:
	AEnemySpawner();
	void SpawnEnemy();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 BossSpawnFrequency = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemyTime = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float EnemyOneDelayMinTime = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float EnemyOneDelayMaxTime = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APawnEnemyShip> EnemyOneClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APawnEnemyShip> EnemyTwoClass;

	class ATwoSidesGameMode* GameModeRef;
	FTimerHandle SpawnEnemyTimer;
	FTimerHandle EnemyOneDelayTimer;

	void SpawnEnemyOne();
	void SpawnEnemyTwo();

};
