// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGAttributeSet, Health);
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldValue);
}
