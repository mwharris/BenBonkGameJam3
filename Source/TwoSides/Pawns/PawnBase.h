#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TWOSIDES_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	APawnBase();
	virtual void HandleDestruction();
	void SetIsBlue(bool IsNewColorBlue, bool IsPlayer);
	bool GetIsBlue();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileBase> ProjectileClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComp;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMaxHealth();
	
	virtual void BeginPlay() override;
	void Fire();
	void ChangeColor();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ShipPivotPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Color", meta = (AllowPrivateAccess = "true"))
	bool IsBlue = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Color", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* BlueMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Color", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* RedMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta=(AllowPrivateAccess="true"))
	UParticleSystem* DeathEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UMatineeCameraShake> DeathCameraShake;

};
