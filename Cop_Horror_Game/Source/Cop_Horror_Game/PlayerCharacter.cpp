// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputDataConfig.h"

APlayerCharacter::APlayerCharacter() = default;

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup input mapping context...
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputContext, 0);

	// ...then bind input actions to events
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (InputActions)
	{
		EnhancedInputComponent->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Move);
		EnhancedInputComponent->BindAction(InputActions->Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Look);
		EnhancedInputComponent->BindAction(InputActions->Crouch, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Crouch);
	}
}

void APlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	FVector2D Axis2DValue = Value.Get<FVector2D>();
	FVector MoveVector = GetActorForwardVector() * Axis2DValue.X + GetActorRightVector() * Axis2DValue.Y;

	AddMovementInput(MoveVector);
}

void APlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	FVector2D Axis2DValue = Value.Get<FVector2D>();
	
	AddControllerYawInput(Axis2DValue.X);
	AddControllerPitchInput(Axis2DValue.Y);
}

void APlayerCharacter::Input_Crouch(const FInputActionValue& Value)
{
	bool BooleanValue = Value.Get<bool>();

	if (BooleanValue) Crouch();
	else UnCrouch();
}
