// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputDataConfig.h"
#include "WeaponComponent.h"
#include "Components/SpotLightComponent.h"
#include "Interactable.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetComponentByClass<UWeaponComponent>();
	Torch = GetComponentByClass<USpotLightComponent>();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckForInteractable();
}

void APlayerCharacter::CheckForInteractable()
{
	FVector CameraLocation; FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, CameraLocation + CameraRotation.Vector() * InteractionDistance, ECC_Visibility);

	// No longer looking at previous interactable
	if (Hit.GetActor() != InteractableActor && IsValid(InteractableActor))
	{
		IInteractable::Execute_OnUnHover(InteractableActor);
		InteractableActor = nullptr;
	}

	// Looking at new interactable
	if (Hit.bBlockingHit && Hit.GetActor()->Implements<UInteractable>())
	{
		InteractableActor = Hit.GetActor();
		IInteractable::Execute_OnHover(InteractableActor);
	}
}

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
		EnhancedInputComponent->BindAction(InputActions->Shoot, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Shoot);
		EnhancedInputComponent->BindAction(InputActions->Reload, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Reload);
		EnhancedInputComponent->BindAction(InputActions->Torch, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_ToggleTorch);
		EnhancedInputComponent->BindAction(InputActions->Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Interact);
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

void APlayerCharacter::Input_Shoot(const FInputActionValue& Value)
{
	if (IsValid(Weapon))
	{
		Weapon->Shoot();
	}
}

void APlayerCharacter::Input_Reload(const FInputActionValue& Value)
{
	if (IsValid(Weapon))
	{
		Weapon->Reload();
	}
}

void APlayerCharacter::Input_ToggleTorch(const FInputActionValue& Value)
{
	if (IsValid(Torch))
	{
		Torch->SetVisibility(!Torch->IsVisible(), true);
	}
}

void APlayerCharacter::Input_Interact(const FInputActionValue& Value)
{
	if (IsValid(InteractableActor))
	{
		IInteractable::Execute_OnInteract(InteractableActor);
	}
}
