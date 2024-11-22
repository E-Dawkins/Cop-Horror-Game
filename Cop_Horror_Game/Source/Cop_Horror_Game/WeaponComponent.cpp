// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::Shoot()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MaxAmmo);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Weapon::Shoot");
}

bool UWeaponComponent::Reload()
{
	if (CurrentAmmo == MaxAmmo)
		return false;

	CurrentAmmo = MaxAmmo;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Weapon::Reload");

	return true;
}
