// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "GameplayTagContainer.h"
#include "RPGPaperCharacter.generated.h"

struct FGameplayTagContainer;
class URPGGameplayAbility;
class URPGAbilitySystemComponent;
class URPGAttributeSet;
class UGameplayEffect;

UCLASS()
class COOLRPG_API ARPGPaperCharacter : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGPaperCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URPGAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	URPGAttributeSet* Attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<URPGGameplayAbility>> GameplayAbilities;

	UPROPERTY()
	uint8 bAbilitiesInitialized:1;

	void AddStartupGameplayAbilities();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintCallable)
	TArray<uint8> GetSaveInfo();

	UFUNCTION(BlueprintCallable)
	void LoadSaveInfo(TArray<uint8> SaveInfo);

	URPGAttributeSet* GetAttributeData();

	friend URPGAttributeSet;
};
