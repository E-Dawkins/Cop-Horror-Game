// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputDataConfig;

UCLASS()
class COP_HORROR_GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void Input_Move(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Look(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Crouch(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category="Player Character|Input")
	UInputMappingContext* InputContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player Character|Input")
	UInputDataConfig* InputActions = nullptr;

};
