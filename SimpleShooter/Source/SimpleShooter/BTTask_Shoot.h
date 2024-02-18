// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_Shoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Shoot();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
