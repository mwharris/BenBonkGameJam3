#include "TwoSides/Pawns/PawnShip.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TwoSides/GameModes/TwoSidesGameMode.h"

APawnShip::APawnShip() 
{

}

void APawnShip::BeginPlay() 
{
    Super::BeginPlay();
    Roll = GetActorRotation().Roll;
    GameModeRef = Cast<ATwoSidesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameModeRef != nullptr) 
    {
        GameModeRef->NotifyUIUpdateHealth();
    }
}

void APawnShip::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &APawnShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnShip::StartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APawnShip::StopFiring);
	PlayerInputComponent->BindAction("ChangeColor", IE_Pressed, this, &APawnShip::ChangeColor);
}

void APawnShip::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    // Horizontal Movement
    FVector Input = FVector(VerticalAxis, HorizontalAxis, 0);
    FVector Movement = Input.GetSafeNormal() * MovementSpeed * DeltaTime;
    FVector NewLocation = GetActorLocation() + FVector(Movement.X, 0, 0);
    SetActorLocation(NewLocation, true);
    // Vertical Movement
    NewLocation = GetActorLocation() + FVector(0, Movement.Y, 0);
    SetActorLocation(NewLocation, true);
    // Rotation
    float RollValue = Roll + (HorizontalAxis * MaxTilt); 
    FRotator TargetRotation = FRotator(0, 0, RollValue);
    FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime, TiltSpeed);
    SetActorRotation(NewRotation);
}

void APawnShip::StartFiring() 
{
    if (!CanFire) return; 
    Fire();   
    CanFire = false;
    GetWorldTimerManager().SetTimer(FireTimer, this, &APawnShip::Fire, FireRate, true);
}

void APawnShip::StopFiring() 
{
    CanFire = true;
    GetWorldTimerManager().ClearTimer(FireTimer);
}

void APawnShip::ChangeColor() 
{
    SetIsBlue(!GetIsBlue(), true);
}

void APawnShip::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

void APawnShip::MoveUp(float AxisValue) 
{
    VerticalAxis = AxisValue;
}

void APawnShip::MoveRight(float AxisValue) 
{
    HorizontalAxis = AxisValue;
}