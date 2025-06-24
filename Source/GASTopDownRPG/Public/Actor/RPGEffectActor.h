// Copyright ZJU doMGameMaker.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "RPGEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT()
struct FEffectKey
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	bool operator==(const FEffectKey& Other) const
	{
		return EffectClass == Other.EffectClass && ASC == Other.ASC;
	}

	friend uint32 GetTypeHash(const FEffectKey& Key)
	{
		return HashCombine(GetTypeHash(Key.EffectClass), GetTypeHash(Key.ASC));
	}
};

USTRUCT(BlueprintType)
struct FEffectContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> EffectClass;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "EffectClass && UGameplayEffect::StaticClass()->GetDefaultObject<UGameplayEffect>()->DurationPolicy == EGameplayEffectDurationType::Infinite"))
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
};

UCLASS()
class GASTOPDOWNRPG_API ARPGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARPGEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, const FEffectContainer& EffectContainer);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	bool bDestroyOnEndOverlap = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	TArray<FEffectContainer> InstantEffects;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	TArray<FEffectContainer> DurationEffects;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	TArray<FEffectContainer> InfiniteEffects;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	// EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY()
	// TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	TMap<FEffectKey, FActiveGameplayEffectHandle> ActiveEffectHandles;
};
