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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MaxTilt = 7;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float TiltSpeed = 80;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.f;

	float VerticalAxis = 0.f;
	float HorizontalAxis = 0.f;
	float Roll = 0.f;
	FTimerHandle FireTimer;
	bool CanFire = true;

	void MoveUp(float AxisValue);
	void MoveRight(float AxisValue);
	void StartFiring();
	void StopFiring();
	void ChangeColor();

};
