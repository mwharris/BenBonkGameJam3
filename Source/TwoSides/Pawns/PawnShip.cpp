#include "TwoSides/Pawns/PawnShip.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnShip::APawnShip() 
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void APawnShip::BeginPlay() 
{
    Super::BeginPlay();
}

void APawnShip::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnShip::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void APawnShip::HandleDestruction() 
{
    Super::HandleDestruction();
}
