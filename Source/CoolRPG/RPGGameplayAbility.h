// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ERPGAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Punch
};

/**
 * 
 */
UCLASS()
class COOLRPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	ERPGAbilityInputID AbilityInputID = ERPGAbilityInputID::None;
};
