// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COP_HORROR_GAME_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	void Shoot();
	bool Reload();

private:
	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (ClampMin = "1"))
	int MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int CurrentAmmo = 0;

};
