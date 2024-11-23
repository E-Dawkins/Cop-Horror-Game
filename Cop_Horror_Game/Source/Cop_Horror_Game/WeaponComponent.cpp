// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::Shoot()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MaxAmmo);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Weapon::Shoot");

	FVector MuzzleFlashPivot = GetRightVector() * MuzzleFlashOffset.X + GetForwardVector() * MuzzleFlashOffset.Y + GetUpVector() * MuzzleFlashOffset.Z;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MuzzleFlashFX, GetComponentLocation() + MuzzleFlashPivot);
}

bool UWeaponComponent::Reload()
{
	if (CurrentAmmo == MaxAmmo)
		return false;

	CurrentAmmo = MaxAmmo;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Weapon::Reload");

	return true;
}
