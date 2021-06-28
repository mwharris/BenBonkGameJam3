#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwoSidesGameMode.generated.h"

UCLASS()
class TWOSIDES_API ATwoSidesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetScore() const;
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyUIUpdateScore();
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyUIUpdateHealth();
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyUIColorChange(bool IsBlue);
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyUIGameOver();

	void ActorDied(AActor* DeadActor);
	void ActorDamaged(AActor* DeadActor);
	void UpdateEnemyCount(int32 Val);
	void SetCurrentEnemiesKilled(float Val);
	int32 GetEnemyCount();
	int32 GetMaxEnemies();
	int32 GetEnemiesKilled();
	int32 GetBossesKilled();
	void SetBossesKilled(int32 Val);
	int32 GetCurrentEnemiesKilled();
	bool IsGameOver() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	class APawnShip* PlayerShip;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 MaxEnemies; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 EnemyCount; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int32 TopScore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class USoundBase* EnemyHitSound;

	float EnemiesKilled = 0.f;
	float BossesKilled = 0.f;
	float CurrentEnemiesKilled = 0.f;
	bool GameOver = false;

};
