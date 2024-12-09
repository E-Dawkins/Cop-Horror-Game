// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::Shoot()
{
	if (CurrentAmmo == 0 || bReloading || bShooting)
		return;

	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MaxAmmo);
	bShooting = true;

	// Trace against environment
	FVector CameraLocation; FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, CameraLocation + CameraRotation.Vector() * Range, ECC_Visibility);

	// Spawn muzzle flash FX
	FVector MuzzleFlashPivot = GetRightVector() * MuzzleFlashOffset.X + GetForwardVector() * MuzzleFlashOffset.Y + GetUpVector() * MuzzleFlashOffset.Z;
	if (UNiagaraComponent* MuzzleFlashComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MuzzleFlashFX, GetComponentLocation() + MuzzleFlashPivot))
	{
		MuzzleFlashComp->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	}

	// If bullet 'hit' something, spawn bullet hit FX
	if (Hit.bBlockingHit)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BulletImpactFX, Hit.ImpactPoint, FMath::GetReflectionVector(CameraRotation.Vector(), Hit.ImpactNormal).Rotation());
		if (UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletImpactDecal, DecalSize, Hit.ImpactPoint, Hit.ImpactNormal.Rotation()))
		{
			Decal->SetLifeSpan(5);
			Decal->SetFadeScreenSize(0.0025f);
		}
	}
}

void UWeaponComponent::Reload()
{
	if (CurrentAmmo == MaxAmmo)
		return;

	CurrentAmmo = MaxAmmo;
	bReloading = true;
}
