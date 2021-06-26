#include "TwoSides/GameModes/TwoSidesGameMode.h"

void ATwoSidesGameMode::ActorDied(AActor* DeadActor) 
{
    UE_LOG(LogTemp, Warning, TEXT("Something died!"));
}
