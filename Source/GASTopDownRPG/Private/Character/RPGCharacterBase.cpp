// Copyright ZJU doMGameMaker.


#include "Character/RPGCharacterBase.h"

ARPGCharacterBase::ARPGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
