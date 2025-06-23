// Copyright ZJU doMGameMaker.


#include "Actor/RPGEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


ARPGEffectActor::ARPGEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void ARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void ARPGEffectActor::ApplyEffectToTarget(AActor* TargetActor, const FEffectContainer& EffectContainer)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(EffectContainer.EffectClass);
	// Handle is a struct that store the actual Data in it and provide a few more functions to use
	// like the two handles here, one stores Effect Context and the other stores Effect Spec
	auto EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectContainer.EffectClass, 1.f, EffectContextHandle);
	const auto ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
 
	// Def is the Gameplay Effect itself
	// const bool bIsInfinite = EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	// {
		// ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	// }
	if (EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite && EffectContainer.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		FEffectKey Key;
		Key.EffectClass = EffectContainer.EffectClass;
		Key.ASC = TargetASC;
		ActiveEffectHandles.Add(Key, ActiveEffectHandle);
	}
}

void ARPGEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const auto& Effect : InstantEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
	for (const auto& Effect : DurationEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
	for (const auto& Effect : InfiniteEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
}

void ARPGEffectActor::OnEndOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;
	
	for (const auto& Effect : InstantEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
	for (const auto& Effect : DurationEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
	for (const auto& Effect : InfiniteEffects)
	{
		if (Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
		
	TArray<FEffectKey> KeysToRemove;
	for (auto& HandlePair : ActiveEffectHandles)
	{
		if (HandlePair.Key.ASC == TargetASC)
		{
			TargetASC->RemoveActiveGameplayEffect(HandlePair.Value, 1);
			KeysToRemove.Add(HandlePair.Key);
		}
	}

	for (auto& Key : KeysToRemove)
	{
		ActiveEffectHandles.Remove(Key);
	}

	if (bDestroyOnEffectRemoval && ActiveEffectHandles.Num() == 0)
	{
		Destroy();
	}
}
