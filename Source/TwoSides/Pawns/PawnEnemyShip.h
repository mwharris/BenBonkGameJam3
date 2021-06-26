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

};
