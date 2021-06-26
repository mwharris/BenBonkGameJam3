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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MinSpeed = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FVector Scale;

	bool MoveDirectionFlag;
	float DistanceFromPlayer = 0.f;
	FVector SpawnLocation;

};