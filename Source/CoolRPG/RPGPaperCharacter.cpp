// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPaperCharacter.h"

#include "RPGAbilitySystemComponent.h"
#include "RPGAttributeSet.h"
#include "RPGGameplayAbility.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


// Sets default values
ARPGPaperCharacter::ARPGPaperCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAbilitiesInitialized = false;
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URPGAttributeSet>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void ARPGPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

// Called every frame
void ARPGPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPGPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (InputComponent && AbilitySystemComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"ERPGAbilityInputID",
			static_cast<int32>(ERPGAbilityInputID::Confirm),
			static_cast<int32>(ERPGAbilityInputID::Cancel));

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ARPGPaperCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	
}

void ARPGPaperCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (InputComponent)
		{
			const FGameplayAbilityInputBinds Binds(
				"Confirm",
				"Cancel",
				"ERPGAbilityInputID",
				static_cast<int32>(ERPGAbilityInputID::Confirm),
				static_cast<int32>(ERPGAbilityInputID::Cancel));

			AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
		}
	}
}

UAbilitySystemComponent* ARPGPaperCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGPaperCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		for (TSubclassOf<URPGGameplayAbility>& StartupAbility : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				StartupAbility, 1,
				static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),
				this));
		}

		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);

			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get(), AbilitySystemComponent);
			}
		}
		bAbilitiesInitialized = true;
	}
}

void ARPGPaperCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
	}
}

void ARPGPaperCharacter::HandleManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnManaChanged(DeltaValue, EventTags);
	}
}

TArray<uint8> ARPGPaperCharacter::GetSaveInfo()
{
	TArray<uint8> ByteData;
	
	// Pass the array to fill with data from Actor
	FMemoryWriter MemWriter(ByteData);

	FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
	// Find only variables with UPROPERTY(SaveGame)
	//Ar.ArIsSaveGame = true;

	if (Attributes)
	{
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Attributes->Serialize(Ar);
		UE_LOG(LogTemp, Error, TEXT("CURRENT HEALTH: %f"), Attributes->Health.GetCurrentValue());
	}

	return ByteData;
}

void ARPGPaperCharacter::LoadSaveInfo(TArray<uint8> SaveInfo)
{
	FMemoryReader MemReader(SaveInfo);

	FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
	//Ar.ArIsSaveGame = true;
	
	if (Attributes)
	{
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Attributes->Serialize(Ar);
		UE_LOG(LogTemp, Error, TEXT("CURRENT HEALTH: %f"), Attributes->Health.GetCurrentValue());
	}
}



