// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputDataConfig;
class UWeaponComponent;
class USpotLightComponent;

UCLASS()
class COP_HORROR_GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	UWeaponComponent* GetWeapon() { return Weapon; }

private:
	UFUNCTION()
	void Input_Move(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Look(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Crouch(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Shoot(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Reload(const FInputActionValue& Value);

	UFUNCTION()
	void Input_ToggleTorch(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category="Player Character|Input")
	UInputMappingContext* InputContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player Character|Input")
	UInputDataConfig* InputActions = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UWeaponComponent* Weapon = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	USpotLightComponent* Torch = nullptr;

};
