// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Target = GetAcceptableActor();
    if (Target)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Target->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Target->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor *UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);

    for (auto &actor : Actors)
    {
        bool HasAcceptableTag = actor->ActorHasTag(UnlockTag);
        bool IsGrabbed = actor->ActorHasTag("Grabbed");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return actor;
        }
    }

    return nullptr;
}