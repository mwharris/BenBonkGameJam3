#pragma once

#include "CoreMinimal.h"
#include "TwoSides/Pawns/PawnBase.h"
#include "PawnShip.generated.h"

UCLASS()
class TWOSIDES_API APawnShip : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnShip();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;

	float VerticalMovement = 0.f;
	float HorizontalMovement = 0.f;

	void MoveUp(float AxisValue);
	void MoveRight(float AxisValue);

};
