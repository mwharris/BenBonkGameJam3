#pragma once

#include "CoreMinimal.h"
#include "TwoSides/Pawns/PawnBase.h"
#include "PawnEnemyShip.generated.h"

UCLASS()
class TWOSIDES_API APawnEnemyShip : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnEnemyShip();
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	int32 GetScoreValue() const;
	bool IsBoss();
	void SetIsBoss(bool Val);

protected:
	UPROPERTY(BlueprintReadOnly)
	class APawnShip* PlayerShip;
	UPROPERTY(BlueprintReadOnly)
	FVector SpawnLocation;
	UPROPERTY(BlueprintReadWrite)
	bool MoveEnabled = false;

	virtual void BeginPlay() override;
	virtual void Fire() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MinSpeed = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FVector Scale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 ScoreValue = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
	float FireDistance = 120.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
	float FireRateMin = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
	float FireRateMax = 2.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	class ATwoSidesGameMode* GameModeRef;
	bool MoveDirectionFlag;
	FTimerHandle ShootTimer;
	bool Shooting = false;
	bool Boss = false;

	void ShootPlayer();

};
