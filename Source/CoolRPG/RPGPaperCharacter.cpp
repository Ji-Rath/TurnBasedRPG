// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPaperCharacter.h"


// Sets default values
ARPGPaperCharacter::ARPGPaperCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARPGPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void ARPGPaperCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ARPGPaperCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

