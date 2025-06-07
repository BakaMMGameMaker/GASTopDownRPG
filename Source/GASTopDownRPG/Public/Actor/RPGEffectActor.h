// Copyright ZJU doMGameMaker.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class GASTOPDOWNRPG_API ARPGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARPGEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
};
