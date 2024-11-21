// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

class UInputAction;

UCLASS()
class COP_HORROR_GAME_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* Move;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Look;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Crouch;
	
};
