// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController *Controller = OwnerComp.GetAIOwner();
    if (Controller == nullptr) return;
    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) return;

    if (IsPlayerInFieldOfView(Controller))
    {
        Controller->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        Controller->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

bool UBTService_PlayerLocationIfSeen::IsPlayerInFieldOfView(AAIController* Controller) const
{
    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) return false;

    FVector EnemyLocation = Controller->GetPawn()->GetActorLocation();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    FVector DirectionToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();

    // Calculate the angle between the enemy's forward vector and the direction to the player
    FVector ForwardVector = Controller->GetPawn()->GetActorForwardVector();
    float DotProduct = FVector::DotProduct(ForwardVector, DirectionToPlayer); // cos value
    float Angle = FMath::Acos(DotProduct);                                    // Returns angle in radians with arccos
    Angle = FMath::RadiansToDegrees(Angle);                                   // Convert angle to degrees

    float FieldOfView = 210.f;

    return Angle < FieldOfView / 2 && Controller->LineOfSightTo(PlayerPawn);
}
